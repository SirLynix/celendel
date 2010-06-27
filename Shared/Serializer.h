#ifndef DEF_SERIALIZER
#define DEF_SERIALIZER

/* Here are all the little functions 'data <=> whatever' */

#include "Constants.h"
#include <QString>
#include <QByteArray>

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text);
QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text);

void extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text);
QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text="");

#endif
