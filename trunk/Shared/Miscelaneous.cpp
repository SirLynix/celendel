#include "Constants.h"
#include <cstdio>
#include <ctime>
#include <QObject>
#include <QFile>
#include <QDir>

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
    {
        hsh.addData(dta,c);
        delete dta;
    }

    return hsh.result();
}

QStringList listFilesInFolder(const QString& folder, const QStringList& filters, const QString& suff)
{
    QStringList l;

    QDir dir(folder);
    dir.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();

    for(int i=0, m=list.size();i<m;++i)
    {
        if(list[i].isDir())
        {
            l+=listFilesInFolder(suff+'/'+list[i].fileName(), suff+'/'+list[i].fileName());
        }
        else
        {
            if(!suff.isEmpty())
                l<<suff+'/'+list[i].fileName();
            else
                l<<list[i].fileName();
        }
    }

    return l;
}

QStringList listFilesInFolder(const QString& folder, const QString& filters)
{
    return listFilesInFolder(folder, filters.split(";;", QString::SkipEmptyParts));
}

quint32 sizeX(const MapArray& m)  { return (quint32)m.shape()[0];}
quint32 sizeY(const MapArray& m)  { return (quint32)m.shape()[1];}
quint32 sizeX(MapArray* m)  { return (quint32)m->shape()[0];}
quint32 sizeY(MapArray* m)  { return (quint32)m->shape()[1];}
