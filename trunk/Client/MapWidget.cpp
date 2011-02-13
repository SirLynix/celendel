#include "MapWidget.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "AboutWindow.h"
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QSettings>

using std::auto_ptr;

sf::Color toSFMLColor(const QColor& col)
{
    return sf::Color(col.red(), col.green(), col.blue(), col.alpha());
}

QColor fromSFMLColor(const sf::Color& col)
{
    return QColor(col.r, col.g, col.b, col.a);
}

MapWidgetScroll::MapWidgetScroll(QWidget* parent) : QScrollArea(parent), map(this, QPoint(0,0), QSize(0,0))
{
    setWidget(&map);
    connect(&timer, SIGNAL(timeout()), this, SLOT(ref()));
    timer.setSingleShot(false);
    timer.start(10);
}

MapWidget::MapWidget(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size), m_map(NULL)
{
    clearRessources();
    m_x=m_y=0;
    m_w=Size.width();
    m_h=Size.height();
    setHighlight(false);
    m_mouseInside=false;
    m_multiSelectionEnabled=false;
    m_mouseDown=false;
}

MapWidget::~MapWidget()
{
    clearRessources();
}

void MapWidgetScroll::sizeUpdate()
{
    if(widget() != NULL)
    {
        if(map.isMapValid())
        {
            widget()->resize(map.m_map->mapSizeX()*BLOC_SIZE, map.m_map->mapSizeY()*BLOC_SIZE);
            viewport()->resize(map.m_map->mapSizeX()*BLOC_SIZE, map.m_map->mapSizeY()*BLOC_SIZE);
            ref();
        }
    }
}

void MapWidgetScroll::ref()
{
    if(widget() != NULL)
    {
        map.setView(-map.pos().x(), -map.pos().y(), viewport()->width(), viewport()->height()); //The coordinates are ALWAYS negatives. Why ? Take a paper.
    }
}

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

    sf::Image* img = new sf::Image;
    if(!img->LoadFromFile(fileName.toStdString()))
    {
        delete img;
        return true;
    }

    delete m_ressources.value(id, NULL);
    m_loadedRessourcesName.remove(m_loadedRessourcesName.key(id));
    m_ressources[id]=img;
    m_loadedRessourcesName[fileName]=id;
    img->SetSmooth(false);
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

    sf::Image* img = new sf::Image;
    if(!img->LoadFromFile(fileName.toStdString()))
    {
        delete img;
        return 0;
    }
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
    img->SetSmooth(false);
    DEB() << fileName << "loaded with RSID " << ch;
    return ch;
}

QList<QPair<QString, RSID> > MapWidget::loadRessourcesPack(const QList<QPair<QString, RSID> >& list)
{
    QList<QPair<QString, RSID> > ret;

    for(int i=0,m=list.size();i<m;++i)
    {
        if(!loadRessource(list[i].first,list[i].second))
            ret << list[i];
    }

    return ret;
}

QList<QPair<QString, RSID> > MapWidget::loadRessources(const QStringList& list)
{
    QList<QPair<QString, RSID> > ret;

    for(int i=0,m=list.size();i<m;++i)
    {
        RSID rsid = loadRessource(list[i]);
        if(rsid != 0)
            ret << qMakePair(list[i], rsid);
    }

    return ret;
}

void MapWidget::clearRessources()
{
    QMap<RSID, sf::Image*>::iterator i = m_ressources.begin();
    while (i != m_ressources.end())
    {
        delete i.value();
        ++i;
    }
    m_ressources.clear();

    m_loadedRessources=1;
    m_ressources[0] = new sf::Image(BLOC_SIZE, BLOC_SIZE, sf::Color(0, 0, 0)); //One black pixel. What else ?

    m_loadedRessourcesName.clear();
}

void MapWidget::setView(int x, int y, int w, int h)
{
    m_x=x; m_y=y; m_w=w; m_h=h;
}

void MapWidget::adjustSize()
{
    if(m_map.get() != NULL)
    {
        resize(m_map->mapSizeX()*BLOC_SIZE, m_map->mapSizeY()*BLOC_SIZE);
        setView(0,0,m_map->mapSizeX()*BLOC_SIZE,m_map->mapSizeY()*BLOC_SIZE);
    }
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
    }

    QFile::remove(TMPPATH);
    #undef TMPPATH

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

    return MapWidget::saveMap(m_map.get(), fileName);
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

    if(m_map.get() != NULL)
    {
        if(!m_map->ressources.isEmpty())
        {
            QMap<RSID, RSID> cor = concatenateRessources(m_map->ressources);

            qint32 mapX = sizeX(m_map->map);
            qint32 mapY = sizeY(m_map->map);

            for(int x=0; x<mapX; ++x)
            {
                for(int y=0; y<mapY; ++y)
                {
                    m_map->map[x][y] = cor.value(m_map->map[x][y], m_map->map[x][y]);
                }
            }
        }
    }

    adjustSize();
}

void MapWidget::OnUpdate()
{
    if(m_map.get() != 0)
    {
        qint32 mapX = sizeX(m_map->map);
        qint32 mapY = sizeY(m_map->map);

        if(mapX>(m_x+m_w)/BLOC_SIZE+2)
            mapX=(m_x+m_w)/BLOC_SIZE+2;

        if(mapY>(m_y+m_h)/BLOC_SIZE+2)
            mapY=(m_y+m_h)/BLOC_SIZE+2;

        int xi=m_x/BLOC_SIZE-2;
        if(xi<0)
            xi=0;

        int yi=m_y/BLOC_SIZE-2;
        if(yi<0)
            yi=0;


        //Clear(sf::Color(200, 200, 200)); //Usefull on resize...

        for(int x=xi; x<mapX; ++x)
            for(int y=yi; y<mapY; ++y)
                drawBloc(x,y,m_map->map[x][y]);

        for(int i=0,m=m_map->mapItems.size();i<m;++i)
            drawBloc(m_map->mapItems[i].coords, m_map->mapItems[i].rsid, m_map->mapItems[i].color);

        if(m_highlightEnabled&&m_mouseInside&&m_highlightedCase.x()>=xi&&m_highlightedCase.x()<mapX&&m_highlightedCase.y()>=yi&&m_highlightedCase.y()<mapY)
        {
            sf::Shape rect=sf::Shape::Rectangle(m_highlightedCase.x()*BLOC_SIZE+2, m_highlightedCase.y()*BLOC_SIZE+2, (m_highlightedCase.x()+1)*BLOC_SIZE-1, (m_highlightedCase.y()+1)*BLOC_SIZE-1,
                                                sf::Color(0, 0, 0, 0), 2.0f, sf::Color(239,228,176,255));
            Draw(rect);
        }

        if(m_multiSelectionEnabled)
        {
            if(m_mouseDown)
            {
                drawBlockBox(m_mouseDownPos,m_highlightedCase,sf::Color(255,150,5,200), 2.f);
            }
            else
            {
                drawBlockBox(m_mouseDownPos,m_mouseUpPos,sf::Color(245,200,50,175), 2.f);
            }
        }

        {
        sf::Shape rect=sf::Shape::Rectangle(m_selectedCase.x()*BLOC_SIZE+2, m_selectedCase.y()*BLOC_SIZE+2, (m_selectedCase.x()+1)*BLOC_SIZE-1, (m_selectedCase.y()+1)*BLOC_SIZE-1,
                                            sf::Color(0, 0, 0, 0), 2.0f, sf::Color(255,201,14,200));
        Draw(rect);
        }
    }
}

void swp (int& x1, int& x2) {int t=x1;x1=x2;x2=t;}

bool MapWidget::caseCanBeSeen(QPoint casePos) const
{
    return pixelCanBeSeen(casePos.x()*BLOC_SIZE,casePos.y()*BLOC_SIZE);
}

bool MapWidget::caseCanBeSeen(int x,int y) const
{
    return pixelCanBeSeen(x*BLOC_SIZE,y*BLOC_SIZE);
}

bool MapWidget::pixelCanBeSeen(QPoint pixel) const
{
    return pixelCanBeSeen(pixel.x(),pixel.y());
}

bool MapWidget::pixelCanBeSeen(int x,int y) const
{
    return (x+BLOC_SIZE)>m_x && (y+BLOC_SIZE)>m_y && x<m_x+m_w && y<m_y+m_h;
}

void MapWidget::drawBlockBox(QPoint casePos, QPoint caseEndPos, const sf::Color& color, float width)
{
    MapArea ma(casePos, caseEndPos); ma.normalise();

    for(int x=ma.leftUp.x(),mx=ma.rightDown.x();x<=mx;++x)
        for(int y=ma.leftUp.y(),my=ma.rightDown.y();y<=my;++y)
            if(caseCanBeSeen(x,y))
                drawBlockHighlight(x,y,color,width);
}

void MapWidget::drawBlockHighlight(const QPoint& casePos, const QColor& color, float width)
{
    drawBlockHighlight(casePos.x(), casePos.y(), toSFMLColor(color), width);
}

void MapWidget::drawBlockHighlight(int x, int y, const sf::Color& color, float width)
{
    sf::Shape rect=sf::Shape::Rectangle(x*BLOC_SIZE+width, y*BLOC_SIZE+width, (x+1)*BLOC_SIZE-(width/2), (y+1)*BLOC_SIZE-(width/2),
                                            sf::Color(0, 0, 0, 0), width, color);
    Draw(rect);
}

void MapWidget::drawBloc(QPoint casePos, RSID id, const QColor& hue)
{
    drawBloc(casePos.x(), casePos.y(), id, sf::Color(hue.red(),hue.green(),hue.blue(),hue.alpha()));
}

void MapWidget::drawBloc(int caseX, int caseY, RSID id, const sf::Color& hue)
{
    if(!caseCanBeSeen(caseX, caseY))
        return;

    sf::Image* im = m_ressources.value(id, m_ressources[0]);

    sf::Sprite spr;
    spr.SetImage(*im);

    spr.SetColor(hue);

    spr.Resize(BLOC_SIZE, BLOC_SIZE);
    spr.SetPosition(caseX*BLOC_SIZE-1, caseY*BLOC_SIZE-1);
    Draw(spr);
}

bool MapWidget::isMapValid() const
{
    return ((m_map.get() != NULL) && m_map->isValid());
}

QPoint MapWidget::posToMap(QPoint pos)
{
    if(!isMapValid())
        return QPoint();

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
    QSFMLCanvas::mouseMoveEvent(event);
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

    QSFMLCanvas::mousePressEvent(event);
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


    QSFMLCanvas::mouseReleaseEvent(event);
}

void MapWidget::leaveEvent (QEvent *event)
{
    m_mouseInside=false;
}

void MapWidget::enterEvent (QEvent *event)
{
    m_mouseInside=true;
}
