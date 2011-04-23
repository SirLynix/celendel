#ifndef DEF_MAPSTRUCTS
#define DEF_MAPSTRUCTS

#include <Boost/multi_array.hpp>
//#include <QVector>
//#include <QString>
class QString;
#include <QMap>
#include <memory>

#define MAX_LOADED_RESSOURCES 2000000000
#define RESSOURCES_FOLDER "Ressources/"
#define MAP_FOLDER "Maps/"
#define BLOC_SIZE 32

#include <QPoint>
#include <QSize>
#include <QColor>

struct MapItem
{
    MapItem(QPoint co = QPoint(), RSID p=0, QString txt = QString(), QColor col = QColor(0,0,0), qreal _hueStr = 0.75f):coords(co), rsid(p), text(txt), color(col), hueStrenght(_hueStr), hidden(false) {}
    QPoint coords;
    RSID rsid;
    QString text;
    QColor color;
    qreal hueStrenght;
    bool hidden;
};

typedef boost::multi_array<RSID, 2> MapArray;
#define mapDim(x,y) boost::extents[x][y]

#define MAP_MAX_SIZE 1024

struct MapInformations
{
    MapInformations() : map(mapDim(0,0)) {}
    QList<MapItem> mapItems;
    MapArray map;
    QString name;

    quint32 mapSizeX() const { return map.shape()[0]; }
    quint32 mapSizeY() const { return map.shape()[1]; }
    QSize mapSize() const { return QSize(mapSizeX(),mapSizeY()); }

    bool isValid() const { return mapSizeX()!=0 && mapSizeY()!=0; }

    private:
        MapInformations(const MapInformations&); ///Non copiable
};

typedef std::auto_ptr<MapInformations> MapPtr;


#endif
