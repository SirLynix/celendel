#include <iostream>

#include <QDir>
#include <QFile>
#include <QDebug>

int countFile(const QString& fileName)
{
    QFile file (fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Error : file " << fileName << " not found.";
        return 0;
    }
    int nb=0;

    while(!file.atEnd())
    {
        file.readLine();
        ++nb;
    }

    qDebug() << "File " << fileName << " : " << nb << "lines.";

    return nb;
}

int countDir(const QString& folderName, const QStringList& filter = QStringList())
{
    QDir dir(folderName);

    if(!dir.exists())
    {
        qDebug() << "Error : folder " << folderName << " not found.";
        return 0;
    }

    QStringList list = dir.entryList(QDir::Files | QDir::AllDirs | QDir::NoSymLinks | QDir::Readable | QDir::NoDotAndDotDot);

    int nb=0;
    int mx=filter.size();

    for(int i=0,m=list.size();i<m;++i)
    {
        QString str(folderName+QDir::separator()+list[i]);
        QDir d(str);
        if(!d.exists())
        {

            if(mx>0)
            {
                for(int j=0;j<mx;++j)
                {
                    if(str.endsWith(filter[j]))
                    {
                        nb+=countFile(str);
                        break;
                    }
                }
            }
            else
                nb+=countFile(str);
        }
        else
            nb+=countDir(str, filter);
    }

    qDebug() << "Folder " << folderName << " : " << nb << "lines.";

    return nb;
}


int main(int argv, char** argc)
{
    if(argv<2)
    {
        qDebug() << "Error : not enought arguments.";
        return 1;
    }
    QString folderName(argc[1]);
    QStringList filter; filter << "*.cpp" << "*.c" << "*.h" << "*.cx" << "*.H" << "*.hpp" << "*.hw" << "*.tpp" << "*.txt" << "*.pro";
    if(argv>2)
    {
        filter=QString(argc[2]).split(' ', QString::SkipEmptyParts);
    }

    qDebug() << "Processing folder " << folderName << ", please wait...";

    int nb = countDir(folderName, filter);
    qDebug() << "Total : " << nb << " lines.";

    return 0;
}
