#ifndef DEF_MAPSTRUCTS
#define DEF_MAPSTRUCTS

#include <Boost/multi_array.hpp>
#include <QVector>

#define CELEM quint32

struct Coords
{
    Coords(CELEM a=0, CELEM b=0): x(a), y(b) {}
    CELEM x;
    CELEM y;
};

struct MapItem
{
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

    private:
        MapInformations(const MapInformations&); ///Non copiable
};


#endif
