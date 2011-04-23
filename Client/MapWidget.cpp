#include <QFile>
#include <QDir>
#include <QDebug>
#include "AboutWindow.h"
#include <QEvent>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QSettings>
#include <QGraphicsPixmapItem>
#include <QGraphicsColorizeEffect>
#include <QGraphicsRectItem>

#include "MapWidget.h"

using std::auto_ptr;

const int& qBound (const int& min,const double& value,const int& max) {return qBound(min, (int)value,max);}

class Flare
{
    public:
        Flare(QColor _color, QPoint _pos, int time)
        {
            color=_color;
            m_time=time;
            pos=_pos;

            m_timer.start();
        }

        qreal getAlpha() const
        {
            return (sin(m_timer.elapsed()/100)+1.0f)/2.0f;
        }

        bool isRunning() const
        {
            return m_timer.elapsed()<m_time;
        }

        QColor color;
        QPoint pos;
    private:
        QTime m_timer;
        int m_time;
};

MapWidget::MapWidget(QWidget* Parent, double FPS) : QGraphicsView(Parent), m_map(NULL), m_FPS(FPS)
{
    setScene(&m_scene);
    clearRessources();

    m_highLightRect=NULL; m_selectedRect=NULL;

    setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setHighlight(false);
    m_mouseInside=false;
    m_multiSelectionEnabled=false;
    m_mouseDown=false;
    m_timer=new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    m_timer->setSingleShot(false);
    m_timer->start(1.f/(FPS*60)*1000);
    m_timerBG=new QTimer(this);
    connect(m_timerBG, SIGNAL(timeout()), this, SLOT(repaintBackground()));
    m_timerBG->setSingleShot(false);
    m_timerBG->start(1.f/FPS*1000);
    repaintBackground();
}

MapWidget::~MapWidget()
{
    clearRessources();
}

void MapWidget::setFPS(double FPS)
{
    m_FPS=FPS;
    m_timerBG->setInterval(1.f/FPS*1000);

    FPS=qBound(0,FPS*60,100);

    m_timer->setInterval(1.f/FPS*1000);

}

void MapWidget::repaintBackground () {m_repaintBG=true;}

void MapWidget::openMapInfoDialog()
{
    QString txt;
    if(m_map.get() != NULL)
    {
        txt += tr("Nom de la carte : %1\n").arg(m_map->name);
        txt += tr("Taille de la carte : (%1x%2)\n").arg(m_map->mapSizeX()).arg(m_map->mapSizeY());
    }
    else
        txt += tr("Aucune carte chargée.\n");

    txt += tr("\nImages chargées : %1\n").arg(m_loadedRessourcesName.size());
    QMap<QString, RSID>::const_iterator i = m_loadedRessourcesName.constBegin();
    while (i !=  m_loadedRessourcesName.constEnd())
    {
        txt += tr("Nom : %1\tReSsource IDentificator : %2\n").arg(i.key()).arg(i.value());
        ++i;
    }
    AboutWindow::open(txt, this);
}

bool MapWidget::loadRessource(QString fileName, RSID id)
{
    if(id == 0 || m_loadedRessourcesName.contains(fileName))
        return true;

    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(RESSOURCES_FOLDER))
        fileName.prepend(RESSOURCES_FOLDER);

    QPixmap* img = new QPixmap;
    if(!img->load(fileName))
    {
        delete img;
        return true;
    }

    *img=img->scaled(BLOC_SIZE, BLOC_SIZE, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    delete m_ressources.value(id, NULL);
    m_loadedRessourcesName.remove(m_loadedRessourcesName.key(id));
    m_ressources[id]=img;
    m_loadedRessourcesName[fileName]=id;
    repaintBackground();
    return false;
}

RSID MapWidget::ressourceRSID(const QString& fileName) const
{
    return m_loadedRessourcesName.value(fileName,0);
}

RSID MapWidget::loadRessource(QString fileName)
{
    {
    RSID rsid=m_loadedRessourcesName.value(fileName);
    if(rsid != 0)
        return rsid;
    }

    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(RESSOURCES_FOLDER))
        fileName.prepend(RESSOURCES_FOLDER);

    QPixmap* img = new QPixmap;
    if(!img->load(fileName))
    {
        delete img;
        return 0;
    }
    *img=img->scaled(BLOC_SIZE, BLOC_SIZE, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    RSID ch=0;
    if(m_loadedRessources==MAX_LOADED_RESSOURCES)
    {

        QList<RSID> list = m_ressources.uniqueKeys();
        for(int i=1,m=list.size();i<m;++i)
        {
            if(list[i] != i)
            {
                ch=i;
                break;
            }
        }
    }
    ch=m_loadedRessources;
    if(ch==0)
    {
        DEB() << "Critical error : image pool is full !";
        delete img;
        return 0;
    }
    m_ressources[ch]=img;
    m_loadedRessourcesName[fileName]=ch;
    ++m_loadedRessources;

    DEB() << fileName << "loaded with RSID " << ch;
    repaintBackground();
    return ch;
}

void MapWidget::clearRessources()
{
    QMap<RSID, QPixmap*>::iterator i = m_ressources.begin();
    while (i != m_ressources.end())
    {
        delete i.value();
        ++i;
    }
    m_ressources.clear();

    m_loadedRessources=1;
    m_ressources[0] = new QPixmap(BLOC_SIZE, BLOC_SIZE);
    m_ressources[0]->fill();

    m_loadedRessourcesName.clear();

    repaintBackground();
}

QList<RSID> MapWidget::loadRessourcesPack(QString fileName)
{
    QList<RSID> ret;

    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(RESSOURCES_FOLDER))
        fileName.prepend(RESSOURCES_FOLDER);

    const QString TMPPATH ("TMPFILE"+QString::number(__LINE__));

    if(!QFile::copy(fileName, TMPPATH))
    {
        DEB() << "Error : " << fileName << " file not found." << TMPPATH;
        return ret;
    }

    QSettings set(TMPPATH, QSettings::IniFormat);

    QStringList keys=set.allKeys();

    clearRessources();

    for(int i=0,size=keys.size();i<size;++i)
    {
        bool ok=false;
        RSID id =  set.value(keys[i]).toUInt(&ok);
        if(ok && !loadRessource(keys[i], id))
            ret << id;
        emit ressourceLoadingProgress(i,size);
    }

    QFile::remove(TMPPATH);
    #undef TMPPATH

    repaintBackground();

    return ret;
}

bool MapWidget::saveRessources(QString fileName)
{
    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(RESSOURCES_FOLDER))
        fileName.prepend(RESSOURCES_FOLDER);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        return true;

    QTextStream out(&file);

    QMap<QString, RSID>::const_iterator i = m_loadedRessourcesName.constBegin();
    while (i != m_loadedRessourcesName.constEnd())
    {
        out << i.key() << "=" << i.value() << '\n';
        ++i;
    }

    return false;
}

bool MapWidget::saveMap(const QString& fileName) const
{
    if(!isMapValid())
        return true;

    return MapWidget::saveCompressedMap(fileName, *m_map, m_loadedRessourcesName);
}

bool MapWidget::saveMap(const MapInformations* map, QString fileName) //Static
{
    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(MAP_FOLDER))
        fileName.prepend(MAP_FOLDER);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        return true;

    QTextStream out(&file);

    qint32 mapX = sizeX(map->map);
    qint32 mapY = sizeY(map->map);

    for(int y=0; y<mapY; ++y)
    {
        for(int x=0; x<mapX; ++x)
        {
            out << map->map[x][y] << ' ';
        }
        out << '\n';
    }

    return false;
}

auto_ptr<MapInformations> MapWidget::makeMap(QPoint size, RSID defaultRSID)
{
    auto_ptr<MapInformations> map;
        map.reset(new MapInformations);
    map->map.resize(mapDim(size.x(), size.y()));
    for(int x=0;x<size.x();++x)
        for(int y=0;y<size.y();++y)
            map->map[x][y]=defaultRSID;

    return map;
}

auto_ptr<MapInformations> MapWidget::loadMap(QString fileName)
{
    auto_ptr<MapInformations> map;

    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(MAP_FOLDER))
        fileName.prepend(MAP_FOLDER);

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return map; //Null pointer

    int sx=0, sy=0;

    while (!file.atEnd())
    {
        int size=QString(file.readLine().simplified()).split(' ', QString::SkipEmptyParts).size();
        if(size!=0)
            sy++;
        if(size>sx)
            sx=size;
    }

    if(sx==0||sy==0)
        return map;

    file.reset(); //Return to the beginning
    map.reset(new MapInformations);
    map->map.resize(mapDim(sx, sy));

    for (int y = 0; !file.atEnd(); ++y)
    {
        QStringList list = QString(file.readLine().simplified()).split(' ', QString::SkipEmptyParts);
        for(int x=0,m=list.size(); x<sx; ++x)
        {
            if(x<m)
            {
                map->map[x][y]=(RSID)list[x].toUInt();
            }
            else
                map->map[x][y]=0;
        }
    }

    return map;
}

void MapWidget::updateRessources(const QMap<QString, RSID>& list)
{
    if(list == m_loadedRessourcesName)
        return;

    QMap<RSID, QPixmap*> tmp;
    QMap<QString, RSID> tmpName;

    int mx=list.size();
    int cprg=0;

    for (QMap<QString, RSID>::const_iterator i = m_loadedRessourcesName.constBegin() ; i != m_loadedRessourcesName.constEnd() ; ++i)
    {
        QPixmap* px = m_ressources.value(i.value(), 0);
        RSID nid=list.value(i.key(),-1);
        if(nid!=-1 && px!=0)
        {
            tmp[nid] = px;
            tmpName[i.key()] = nid;
            emit ressourceLoadingProgress(++cprg,mx);
        }
        else
            delete px;

    }

    m_ressources=tmp;
    m_loadedRessourcesName=tmpName;

    for (QMap<QString, RSID>::const_iterator i = list.constBegin() ; i != list.constEnd() ; ++i)
    {
        if(!m_loadedRessourcesName.contains(i.key()))
        {
            loadRessource(i.key(), i.value());
            emit ressourceLoadingProgress(++cprg,mx);
        }
    }



    m_loadedRessources=m_loadedRessourcesName.size()+1;
    m_ressources[0] = new QPixmap(BLOC_SIZE, BLOC_SIZE);
    m_ressources[0]->fill();
    m_loadedRessourcesName[""]=0;
    emit ressourceLoadingProgress(mx,mx);
}

QMap<RSID, RSID> MapWidget::concatenateRessources(const QMap<RSID, QString>& other)
{
    QMap<RSID, RSID> ret;

    QMap<RSID, QString>::const_iterator i = other.constBegin();
    while (i != other.constEnd())
    {
        ret[i.key()]=loadRessource(i.value());
        ++i;
    }

    return ret;
}

void MapWidget::setMap(MapPtr map)
{
    m_map=map;

    if(m_map.get() != NULL && !m_map->isValid())
        m_map.reset(NULL);

    repaintBackground();
}

void MapWidget::clearTemporaryItems()
{
    for(int i=0,m=m_tempItems.size();i<m;++i)
    {
        m_scene.removeItem(m_tempItems[i]);
        delete m_tempItems[i];
    }
    m_tempItems.clear();
}

void MapWidget::onUpdate()
{
    if(m_map.get() != 0)
    {
        if(m_repaintBG)
        {
            QTime timeWatcher; timeWatcher.start();

            m_repaintBG=false;
            m_scene.clear();
            m_tempItems.clear();

            qint32 mapX = sizeX(m_map->map);
            qint32 mapY = sizeY(m_map->map);

            for(int x=0; x<mapX; ++x)
                for(int y=0; y<mapY; ++y)
                {
                    drawBloc(x,y,m_map->map[x][y]);
                    drawBlockHighlight(x, y, QColor(25,25,25,150), 1.f, true);
                }

            for(int i=0,m=m_map->mapItems.size();i<m;++i)
                drawBloc(m_map->mapItems[i].coords, m_map->mapItems[i].rsid, m_map->mapItems[i].color, m_map->mapItems[i].hueStrenght);


            if(timeWatcher.elapsed() > 1.0f/m_FPS*1000)
            {
                setFPS((1.f/(static_cast<double>(timeWatcher.elapsed())/1000.f)/4));
                DEB() << "WARNING : New FPS = " <<m_FPS;
            }

        }

        clearTemporaryItems();

        if(m_highlightEnabled&&m_mouseInside)
        {
            drawBlockHighlight(m_highlightedCase, QColor(255,170,25,185), 2.f);
        }

        if(m_multiSelectionEnabled)
        {
            if(m_mouseDown)
            {
                drawBlockBox(m_mouseDownPos,m_highlightedCase,QColor(255,150,5,200), 2.f);
            }
            else
            {
                drawBlockBox(m_mouseDownPos,m_mouseUpPos,QColor(245,200,50,175), 2.f);
            }
        }
        drawBlockHighlight(m_selectedCase, QColor(255,170,25,185), 2.f);

        cleanFlares();
        for(int i=0,m=m_flares.size();i<m;++i)
        {
            QColor col = m_flares[i]->color;
            col.setAlphaF(m_flares[i]->getAlpha());
            drawBlockHighlight(m_flares[i]->pos, col, 2.f);
        }

    }
}

void swp (int& x1, int& x2) {int t=x1;x1=x2;x2=t;}

void MapWidget::drawBlockBox(QPointF casePos, QPointF caseEndPos, const QColor& color, float width)
{
    drawBlockBox(QPoint(casePos.x(), casePos.y()), QPoint(caseEndPos.x(), caseEndPos.y()), color, width);
}

void MapWidget::drawBlockBox(QPoint casePos, QPoint caseEndPos, const QColor& color, float width)
{
    MapArea ma(casePos, caseEndPos); ma.normalise();

    for(int x=ma.leftUp.x(),mx=ma.rightDown.x();x<=mx;++x)
        for(int y=ma.leftUp.y(),my=ma.rightDown.y();y<=my;++y)
            drawBlockHighlight(x,y,color,width);
}

void MapWidget::drawBlockHighlight(const QPointF& casePos, const QColor& color, float width)
{
    drawBlockHighlight(QPoint(casePos.x(), casePos.y()), color, width);
}

void MapWidget::drawBlockHighlight(const QPoint& casePos, const QColor& color, float width)
{
    drawBlockHighlight(casePos.x(), casePos.y(), color, width);
}

void MapWidget::drawBlockHighlight(int x, int y, const QColor& color, float width, bool noDelete)
{
    QPen pe (color); pe.setWidthF(width); pe.setJoinStyle(Qt::MiterJoin);
    QGraphicsRectItem* it = m_scene.addRect(x*BLOC_SIZE, y*BLOC_SIZE,BLOC_SIZE, BLOC_SIZE,  pe);
    if(!noDelete)
        m_tempItems.append(it);
}

void MapWidget::drawBloc(QPoint casePos, RSID id, const QColor& hue, qreal hueStrenght)
{
    drawBloc(casePos.x(), casePos.y(), id, hue, hueStrenght);
}

void MapWidget::drawBloc(int caseX, int caseY, RSID id, const QColor& hue, qreal hueStrenght)
{
    QGraphicsPixmapItem *it = m_scene.addPixmap(*m_ressources.value(id, m_ressources[0]));
    it->setPos(caseX*BLOC_SIZE, caseY*BLOC_SIZE);
    if(hue != QColor(255,255,255) && hueStrenght != 0)
    {
        QGraphicsColorizeEffect *eff = new QGraphicsColorizeEffect;
        eff->setColor(hue);
        eff->setStrength(hueStrenght);
        it->setGraphicsEffect(eff);
        it->setOpacity(hue.alphaF());
    }
}

bool MapWidget::isMapValid() const
{
    return ((m_map.get() != NULL) && m_map->isValid());
}

QPoint MapWidget::posToMap(QPoint p)
{
    if(!isMapValid())
        return QPoint();

    QPointF pos=mapToScene(p);

    int mx=m_map->mapSizeX();
    int my=m_map->mapSizeY();

    int x = pos.x()/BLOC_SIZE;
    if(x<0)
        x=0;
    if(x>mx)
        x=mx;

    int y = pos.y()/BLOC_SIZE;
    if(y<0)
        y=0;
    if(y>my)
        y=my;

    return QPoint(x,y);
}

void MapWidget::scrollContentsBy (int dx, int dy)
{
    m_highlightedCase.rx() -= (dx/BLOC_SIZE);
    m_highlightedCase.ry() -= (dy/BLOC_SIZE);
    if(m_highlightEnabled)
        emit highlightedCaseChanged(m_highlightedCase);

    QGraphicsView::scrollContentsBy(dx,dy);
}

void MapWidget::mouseMoveEvent (QMouseEvent *event)
{
    if(isMapValid())
    {
        QPoint p=posToMap(event->pos());
        if(p!=m_highlightedCase)
        {
            m_highlightedCase=p;
            if(m_highlightEnabled)
                emit highlightedCaseChanged(p);
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MapWidget::setHighlight(bool highlight)
{
    m_highlightEnabled=highlight;
    setMouseTracking(highlight);
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isMapValid())
        {
            m_mouseDown=true;
            m_mouseDownPos=posToMap(event->pos());
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void MapWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isMapValid())
        {
            m_selectedCase = posToMap(event->pos());
            emit mapClicked(m_selectedCase);
            m_mouseDown=false;
            m_mouseUpPos=m_selectedCase;
            MapArea ma(m_mouseDownPos,m_mouseUpPos); ma.normalise();
            emit mapAreaSelected(ma);
        }

    }

    QGraphicsView::mouseReleaseEvent(event);
}

void MapWidget::leaveEvent(QEvent*)
{
    m_mouseInside=false;
}

void MapWidget::enterEvent(QEvent*)
{
    m_mouseInside=true;
}

void MapWidget::flare(QPoint c, CLID w)
{
    static QStringList colors = QColor::colorNames();
    static int m=0;
    static bool first=true;
    if(first)
    {
        colors.removeOne("black");
        colors.removeOne("indigo");
        colors.removeOne("darkslategrey");
        colors.removeOne("darkslategray");
        colors.removeOne("midnightblue");

        m=colors.size();
        first = false;
    }

    flare(c, colors[w%m]);
}

void MapWidget::flare(QPoint c, QColor col)
{
    if(!isMapValid())
        return;

    Flare* fl = new Flare(col,c,3000);
    m_flares.append(fl);
}

void MapWidget::cleanFlares()
{
    for(int i=0,m=m_flares.size();i<m;++i)
        if(!m_flares[i]->isRunning())
        {
            delete m_flares[i];
            m_flares[i]=NULL;
        }
    m_flares.removeAll(NULL);
}
