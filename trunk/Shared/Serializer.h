#ifndef DEF_SERIALIZER
#define DEF_SERIALIZER

            /// The serializers ///
/* Here are all the little functions 'data <=> whatever' */

/* Workers :
    - Gigotdarnaud
*/

#include "Constants.h"
#include "MapStructs.h"
#include <QStringList>
#include <QByteArray>

bool extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text, CLID& sender);
QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text, CLID sender);

bool extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text);
QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text="");

bool extractGMElectData(QByteArray& data, CLID& ID);
QByteArray serialiseGMElectData(CLID ID);

bool extractSetCLIDData(QByteArray& data, CLID& ID);
QByteArray serialiseSetCLIDData(CLID ID);

bool extractNewGMData(QByteArray& data, CLID& ID);
QByteArray serialiseNewGMData(CLID ID);

bool extractVotedData(QByteArray& data, CLID& fID, CLID& tID);
QByteArray serialiseVotedData(CLID fID, CLID tID);

bool extractNewNickData(QByteArray& data, CLID& ID, QString& nick);
QByteArray serialiseNewNickData(CLID ID, const QString& nick);

bool extractSetNickData(QByteArray& data, QString& ID);
QByteArray serialiseSetNickData(const QString& ID);

bool extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE& dropType, QString& reason);
QByteArray serialiseGTFOLynixData(CLID ID, ENUM_TYPE dropType, const QString& reason="");

bool extractTODData(QByteArray& data, QString& when);
QByteArray serialiseTODData(const QString& when);

bool extractLocationData(QByteArray& data, QString& where);
QByteArray serialiseLocationData(const QString& where);

bool extractServerInformationsData(QByteArray& data, ServerInformations& si);
QByteArray serialiseServerInformationsData(const ServerInformations& si);

bool extractMOTDData(QByteArray& data, QString& motd);
QByteArray serialiseMOTDData(const QString& motd);

bool extractMapInformationsData(QByteArray& data, MapInformations& mi);
QByteArray serialiseMapInformationsData(const MapInformations& mi);

bool extractMapItemsInformationsData(QByteArray& data, QList<MapItem>& mi);
QByteArray serialiseMapItemsInformationsData(const QList<MapItem>& mi);

bool extractDiceRollData(QByteArray& data, CLID& ID, quint16& result);
QByteArray serialiseDiceRollData(CLID ID, quint16 result);

bool extractPlaySoundData(QByteArray& data, QString& lib, RSID& ID);
QByteArray serialisePlaySoundData(const QString& lib, RSID ID);

bool extractServerNameData(QByteArray& data, QString& name);
QByteArray serialiseServerNameData(const QString& name);

bool extractClientJoinedData(QByteArray& data, CLID& ID);
QByteArray serialiseClientJoinedData(const CLID& ID);

bool extractClientLeftData(QByteArray& data, CLID& ID);
QByteArray serialiseClientLeftData(const CLID& ID);

bool extractUnbanData(QByteArray& data, QString& IP);
QByteArray serialiseUnbanData(const QString& IP);

bool extractAllNarrationData(QByteArray& data, QString& txt);
QByteArray serialiseAllNarrationData(const QString& txt);

bool extractSyncLibsData(QByteArray& data, QStringList& libs, QList<LVER>& ver);
QByteArray serialiseSyncLibsData(const QStringList& libs, const QList<LVER>& ver);

#endif
