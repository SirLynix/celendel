#ifndef DEF_MAPSTRUCTS
#define DEF_MAPSTRUCTS

#include <Boost/multi_array.hpp>
#include <QVector>
#include <QString>

#define CELEM quint32

struct Coords
{
    Coords(CELEM a=0, CELEM b=0): x(a), y(b) {}
    CELEM x;
    CELEM y;
};

struct MapItem
{
    MapItem(Coords co = Coords(), RSID p=0):coords(co), pixID(p) {}
    Coords coords;
    RSID pixID;
};

typedef boost::multi_array<RSID, 2> MapArray;
#define mapDim(x,y) boost::extents[x][y]

struct MapInformations
{
    MapInformations() : map(mapDim(0,0)) {}
    QList<MapItem> mapItems;
    MapArray map;
    QString name;

    quint32 mapSizeX() const { return map.shape()[0]; }
    quint32 mapSizeY() const { return map.shape()[1]; }
    Coords mapSize() const { return Coords(mapSizeX(),mapSizeY()); }

    private:
        MapInformations(const MapInformations&); ///Non copiable
};


#endif
