#include "MapWidget.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "AboutWindow.h"
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>

using std::auto_ptr;

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
        qDebug() << "Critical error : image pool is full !";
        delete img;
        return 0;
    }
    m_ressources[ch]=img;
    m_loadedRessourcesName[fileName]=ch;
    ++m_loadedRessources;
    qDebug() << fileName << "loaded with RSID " << ch;
    return ch;
}

QList<RSID> MapWidget::loadRessourcesPack(const QStringList& list, bool exclusive)
{
    QList<RSID> ret;

    for(int i=0,m=list.size();i<m;++i)
    {
        RSID rsid = loadRessource(list[i]);
        if(rsid != 0 || exclusive)
            ret << rsid;
    }

    return ret;
}

QList<RSID> MapWidget::loadRessourcesFolder(QString folderName, bool exclusive)
{
    QStringList list;

    if(QDir::isRelativePath(folderName)&&!folderName.startsWith(RESSOURCES_FOLDER))
        folderName.prepend(RESSOURCES_FOLDER);

    QDir dir(folderName);

    if(exclusive)
        clearRessources();

    if(!dir.exists())
        return QList<RSID> ();

    list = dir.entryList(QDir::Files|QDir::NoDotAndDotDot|QDir::Readable,QDir::Name);

    return loadRessourcesPack(list, exclusive);
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
    m_ressources[0] = new sf::Image(1, 10, sf::Color(0, 0, 0)); //One black pixel. What else ?

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
      //  setMaximumSize(m_map->mapSizeX()*BLOC_SIZE, m_map->mapSizeY()*BLOC_SIZE);
       // setFixedSize(m_map->mapSizeX()*BLOC_SIZE, m_map->mapSizeY()*BLOC_SIZE);
    }
}

QList<RSID> MapWidget::loadRessourcesPack(QString fileName, bool exclusive)
{
    QList<RSID> ret;

    if(QDir::isRelativePath(fileName)&&!fileName.startsWith(RESSOURCES_FOLDER))
        fileName.prepend(RESSOURCES_FOLDER);


    QFile file (fileName);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << fileName << "file not found";
        return ret; // Error : file not found
    }

    if(exclusive)
        clearRessources();

    while (!file.atEnd())
    {
        QString line=file.readLine().trimmed();
        RSID rsid = loadRessource(line);
        if(rsid != 0 || exclusive)
            ret << rsid;
    }

    return ret;
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


        Clear(sf::Color(200, 200, 200)); //Usefull on resize...

        for(int x=xi; x<mapX; ++x)
        {
            for(int y=yi; y<mapY; ++y)
            {
                sf::Image* im = m_ressources.value(m_map->map[x][y],NULL);
                if(im==NULL)
                    im=m_ressources[0];

                sf::Sprite spr;
                spr.SetImage(*im);
                spr.Resize(BLOC_SIZE, BLOC_SIZE);
                spr.SetPosition(x*BLOC_SIZE-1, y*BLOC_SIZE-1);
                Draw(spr);

            }
        }

        if(m_highlightEnabled&&m_mouseInside&&m_highlightedCase.x()>=xi&&m_highlightedCase.x()<mapX&&m_highlightedCase.y()>=yi&&m_highlightedCase.y()<mapY)
        {
            sf::Shape rect=sf::Shape::Rectangle(m_highlightedCase.x()*BLOC_SIZE+2, m_highlightedCase.y()*BLOC_SIZE+2, (m_highlightedCase.x()+1)*BLOC_SIZE-1, (m_highlightedCase.y()+1)*BLOC_SIZE-1,
                                                sf::Color(0, 0, 0, 0), 2.0f, sf::Color(239,228,176,255));
            Draw(rect);
        }

        {
        sf::Shape rect=sf::Shape::Rectangle(m_selectedCase.x()*BLOC_SIZE+2, m_selectedCase.y()*BLOC_SIZE+2, (m_selectedCase.x()+1)*BLOC_SIZE-1, (m_selectedCase.y()+1)*BLOC_SIZE-1,
                                            sf::Color(0, 0, 0, 0), 2.0f, sf::Color(255,201,14,200));
        Draw(rect);
        }
    }
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
    if(m_highlightEnabled&&isMapValid())
    {
        QPoint p=posToMap(event->pos());
        if(p!=m_highlightedCase)
        {
            m_highlightedCase=p;
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

void MapWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isMapValid())
        {
            m_selectedCase = posToMap(event->pos());
            emit mapClicked(m_selectedCase);
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
