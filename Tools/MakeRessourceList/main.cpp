#include <iostream>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QDebug>


int makeList(const QString& folder, const QStringList& filter, QTextStream& out, int from=0, const QString& prefixRem=QString())
{
    QDir dir(folder);

    qDebug() << "Processing : " << folder;

    QFileInfoList lst = dir.entryInfoList(filter, QDir::NoDotAndDotDot|QDir::Readable|QDir::Files|QDir::AllDirs, QDir::DirsLast);

    for(int i=0,size=lst.size();i<size;++i)
    {
        if(lst[i].isDir())
        {
            from = makeList(lst[i].filePath(), filter, out, from, prefixRem);
        }
        else
        {
            QString pth(lst[i].filePath());
            if(!prefixRem.isEmpty() && pth.startsWith(prefixRem))
                pth=pth.mid(prefixRem.size());
            out << from << "=" << pth << '\n';
            ++from;
        }
    }

    return from;
}


int main(int argv, char** argc)
{
    if(argv<2)
    {
        qDebug() << "Error : not enought arguments.";
        return 1;
    }
    QString folderName(argc[1]);
    QString prefixRem; QString fileName(folderName+"/fileList.list");
    QStringList fil; fil<<"*.png"<<"*.bmp"<<"*.gif"<<"*.jpg"<<"*.jpeg";
    if(argv>2)
    {
        prefixRem=argc[2];
    }
    if(argv>3)
    {
        fileName=argc[3];
    }
    if(argv>4)
    {
        fil=QString(argc[4]).split(' ', QString::SkipEmptyParts);
    }

    QFile f (fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "ERROR : Cannot open file " << fileName;
        return 1;
    }
    QTextStream out (&f);

    folderName.replace('\\', '/');
    prefixRem.replace('\\', '/');

    makeList(folderName,fil,out,0,prefixRem);

    qDebug() << "Done, to file " << fileName;

    return 0;
}
