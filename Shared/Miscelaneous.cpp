#include "Constants.h"
#include <cstdio>
#include <ctime>
#include <QObject>
#include <QFile>

#define tr(a) QObject::tr(a)

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

QString hashFile(const QString& filename, QCryptographicHash::Algorithm al)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return QString();
    QCryptographicHash hsh(al);

    #define BUFF_SIZE 1024
    char *dta=new char[BUFF_SIZE];
    qint64 c=0;
    while((c=file.read(dta, BUFF_SIZE))>0)
        hsh.addData(dta,c);

    return hsh.result();
}

quint32 sizeX(const MapArray& m)  { return (quint32)m.shape()[0];}
quint32 sizeY(const MapArray& m)  { return (quint32)m.shape()[1];}
quint32 sizeX(MapArray* m)  { return (quint32)m->shape()[0];}
quint32 sizeY(MapArray* m)  { return (quint32)m->shape()[1];}
