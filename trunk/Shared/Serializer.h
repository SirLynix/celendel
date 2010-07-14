#ifndef DEF_SERIALIZER
#define DEF_SERIALIZER

            /// The serializers ///
/* Here are all the little functions 'data <=> whatever' */

/* Workers :
    - Gigotdarnaud
*/

#include "Constants.h"
#include "MapStructs.h"
#include <QString>
#include <QByteArray>

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text, CLID& sender);
QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text, CLID sender);

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

void extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE& dropType, QString& reason);
QByteArray serialiseGTFOLynixData(CLID ID, ENUM_TYPE dropType, const QString& reason="");

void extractTODData(QByteArray& data, QString& when);
QByteArray serialiseTODData(const QString& when);

void extractLocationData(QByteArray& data, QString& where);
QByteArray serialiseLocationData(const QString& where);

void extractServerInformationsData(QByteArray& data, ServerInformations& si);
QByteArray serialiseServerInformationsData(const ServerInformations& si);

void extractMOTDData(QByteArray& data, QString& motd);
QByteArray serialiseMOTDData(const QString& motd);

void extractMapInformationsData(QByteArray& data, MapInformations& mi);
QByteArray serialiseMapInformationsData(const MapInformations& mi);

void extractMapItemsInformationsData(QByteArray& data, QList<MapItem>& mi);
QByteArray serialiseMapItemsInformationsData(const QList<MapItem>& mi);

void extractDiceRollData(QByteArray& data, CLID& ID, quint16& result);
QByteArray serialiseDiceRollData(CLID ID, quint16 result);

void extractPlaySoundData(QByteArray& data, RSID& ID);
QByteArray serialisePlaySoundData(RSID ID);

void extractServerNameData(QByteArray& data, QString& name);
QByteArray serialiseServerNameData(const QString& name);

void extractClientJoinedData(QByteArray& data, CLID& ID);
QByteArray serialiseClientJoinedData(const CLID& ID);

void extractClientLeftData(QByteArray& data, CLID& ID);
QByteArray serialiseClientLeftData(const CLID& ID);

void extractUnbanData(QByteArray& data, QString& IP);
QByteArray serialiseUnbanData(const QString& IP);

void extractAllNarrationData(QByteArray& data, QString& txt);
QByteArray serialiseAllNarrationData(const QString& txt);

#endif
