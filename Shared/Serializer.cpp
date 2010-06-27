#include "Serializer.h"
#include <QDataStream>

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text)
{
    QDataStream in(data);

    in>>canal;
    in>>text;
}

QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text)
{
    QByteArray data;
    QDataStream out(data);

    out<<(ENUM_TYPE)canal;
    out<<text;

    return data;
}

void extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text)
{
    QDataStream in(data);

    in>>error_type;
    in>>text;
}

QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text)
{
    QByteArray data;
    QDataStream out(data);

    out<<(ENUM_TYPE)error_type;
    out<<text;

    return data;
}
