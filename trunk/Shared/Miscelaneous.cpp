#include "Constants.h"
#include <cstdio>
#include <ctime>
#include <QObject>
#include <QFile>
#include <QDir>

#define tr(a) QObject::tr(a)

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return static_cast<int>(min+(static_cast<float>(rand())/RAND_MAX*(max-min+1)));}

bool mkpath(const QString& s)
{
    QDir d;
    return !d.mkpath(s);
}

bool RemoveDirectory(QDir &aDir)
{
    bool err=false;
    if (aDir.exists())
    {
        QFileInfoList entries = aDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

        for (int i=0,m=entries.size();i<m;++i)
        {
            QString path = entries[i].absoluteFilePath();
            if (!entries[i].isDir())
            {
                QFile file(path);
                if (!file.remove())
                    err=true;
            }
            else
            {
                QDir d=QDir(path);
                err=RemoveDirectory(d);
            }
        }
        if (!aDir.rmdir(aDir.absolutePath()))
            err = true;
    }
    return err;
}

bool rmWholeDir(const QString& dir)
{
    QDir d(dir);
    return !RemoveDirectory(d);
}

bool cpyWholeDir(const QString& from, const QString& to)
{
    bool err=false;
    QStringList li=listFilesInFolder(from);
    for(int i=0,m=li.size();i<m;++i)
    {
        QString fi=to+li[i];
        mkpath(fi.left(fi.lastIndexOf('/')));
        if(!QFile::copy(from+li[i],fi))
            err=true;
    }
    return err;
}

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
            l+=listFilesInFolder(folder+list[i].fileName()+'/', filters, suff+list[i].fileName()+'/');
        }
        else
        {
            if(!suff.isEmpty())
                l<<suff+list[i].fileName();
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

quint32 sizeX(const MapArray& m)  { return static_cast<quint32>(m.shape()[0]);}
quint32 sizeY(const MapArray& m)  { return static_cast<quint32>(m.shape()[1]);}
quint32 sizeX(MapArray* m)  { return static_cast<quint32>(m->shape()[0]);}
quint32 sizeY(MapArray* m)  { return static_cast<quint32>(m->shape()[1]);}
