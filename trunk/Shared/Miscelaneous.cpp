#include "Constants.h"
#include <cstdio>
#include <ctime>
#include <QObject>

#define tr(a) QObject::tr(a)

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

quint32 sizeX(const MapArray& m)  { return (quint32)m.shape()[0];}
quint32 sizeY(const MapArray& m)  { return (quint32)m.shape()[1];}
quint32 sizeX(MapArray* m)  { return (quint32)m->shape()[0];}
quint32 sizeY(MapArray* m)  { return (quint32)m->shape()[1];}
