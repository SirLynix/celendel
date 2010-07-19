#ifndef GLOBAL_H
#define GLOBAL_H

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <QMetaType>
#include <QVector>

typedef QVector<ALshort> ALshortVector;
Q_DECLARE_METATYPE(ALshortVector);

#endif // GLOBAL_H
