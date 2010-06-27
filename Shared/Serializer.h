#ifndef DEF_SERIALIZER
#define DEF_SERIALIZER

            /// The serializers ///
/* Here are all the little functions 'data <=> whatever' */

/* Workers :
    - Gigotdarnaud
*/

#include "Constants.h"
#include <QString>
#include <QByteArray>

int alea(int min,int max);

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text);
QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text);

void extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text);
QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text="");

void extractGMElectData(QByteArray& data, CLID& ID);
QByteArray serialiseGMElectData(CLID ID);

void extractSetCLIDData(QByteArray& data, CLID& ID);
QByteArray serialiseSetCLIDData(CLID ID);

void extractNewGMData(QByteArray& data, CLID& ID);
QByteArray serialiseNewGMData(CLID ID);

void extractVotedData(QByteArray& data, CLID& fID, CLID& tID);
QByteArray serialiseVotedData(CLID fID, CLID tID);

void extractNewNickData(QByteArray& data, CLID& ID, QString& nick);
QByteArray serialiseNewNickData(CLID ID, const QString& nick);

void extractSetNickData(QByteArray& data, QString& ID);
QByteArray serialiseSetNickData(const QString& ID);

void extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE dropType, QString& reason);
QByteArray serialiseGTFOLynixData(CLID ID, ENUM_TYPE dropType, const QString& reason="");

void extractTODData(QByteArray& data, QString& when);
QByteArray serialiseTODData(const QString& when);

void extractLocationData(QByteArray& data, QString& where);
QByteArray serialiseLocationData(const QString& where);

void extractServerInformationsData(QByteArray& data, ServerInformations& si);
QByteArray serialiseServerInformationsData(const ServerInformations& si);

#endif
