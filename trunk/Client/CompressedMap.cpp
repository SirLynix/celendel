#include "../Shared/Constants.h"
#include "../Shared/Serializer.h"
#include "MapWidget.h"

#include <QFile>

#define MAGIC_CONSTANT 0x7331

void MapWidget::saveCompressedMap(QDataStream& out, const MapInformations& map, const QMap<QString, RSID>& rss)
{
    out << static_cast<qint32>(MAGIC_CONSTANT);
    out << serialiseMapInformationsData(map);
    out << serialiseUpdateRessourcesData(rss);
}

bool MapWidget::saveCompressedMap(QString fileName, const MapInformations& map, const QMap<QString, RSID>& rss)
{
    QFile file (fileName);

    if(!file.open(QIODevice::WriteOnly))
        return true;

    QDataStream out(&file);

    saveCompressedMap(out, map, rss);

    return false;
}

bool MapWidget::loadCompressedMap(QDataStream& in, MapInformations& map, QMap<QString, RSID>& rss)
{
    qint32 cstn=0;
    in >> cstn;

    if(cstn != MAGIC_CONSTANT)
    {
        DEB() << "ERROR : Invalid header";
        return true;
    }

    QByteArray ba;
    in >> ba;
    if(in.status()!=QDataStream::Ok || extractMapInformationsData(ba, map))
        return true;

    ba.clear();
    in >> ba;
    if(in.status()!=QDataStream::Ok || extractUpdateRessourcesData(ba, rss))
        return true;

    return false;
}

bool MapWidget::loadCompressedMap(QString fileName, MapInformations& map, QMap<QString, RSID>& rss)
{
    QFile file (fileName);

    if(!file.open(QIODevice::ReadOnly))
        return true;

    QDataStream out(&file);

    return loadCompressedMap(out, map, rss);
}

