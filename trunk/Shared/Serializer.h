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
#include <QPair>

#include <QDataStream>
QDataStream &operator<<(QDataStream & ds, const PlayerInformations& p);
QDataStream &operator>>(QDataStream & q, PlayerInformations& p);

QDataStream &operator<<(QDataStream & ds, const EntityInformations& e);
QDataStream &operator>>(QDataStream & ds, EntityInformations& e);

QDataStream &operator<<(QDataStream & ds, const EntityData& p);
QDataStream &operator>>(QDataStream & q, EntityData& p);

bool extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& language, QString& text, CLID& sender); // The language string will be IGNORED if the canal is not RP chat.
QByteArray serialiseChatData(ENUM_TYPE canal, const QString& language, const QString& text, CLID sender); // An empty language string will make the message fully understandable to everyone.

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

bool extractPlaySoundData(QByteArray& data, QString& lib, QString& sound);
QByteArray serialisePlaySoundData(const QString& lib, const QString& sound);

bool extractServerNameData(QByteArray& data, QString& name);
QByteArray serialiseServerNameData(const QString& name);

bool extractClientJoinedData(QByteArray& data, CLID& ID, QString& IP);
QByteArray serialiseClientJoinedData(const CLID& ID, const QString& IP);

bool extractClientLeftData(QByteArray& data, CLID& ID);
QByteArray serialiseClientLeftData(const CLID& ID);

bool extractUnbanData(QByteArray& data, QString& IP);
QByteArray serialiseUnbanData(const QString& IP);

bool extractAllNarrationData(QByteArray& data, QString& txt);
QByteArray serialiseAllNarrationData(const QString& txt);

bool extractSyncLibsData(QByteArray& data, QList<SoundLibInformations>& libs);
QByteArray serialiseSyncLibsData(const QList<SoundLibInformations>& libs);

bool extractLanguagesData(QByteArray& data, QList<QPair<QString, QString> >& languages);
QByteArray serialiseLanguagesData(const QList<QPair<QString, QString> >& languages);

bool extractAddDicoData(QByteArray& data, QString& name, QString& content);
QByteArray serialiseAddDicoData(const QString& name, const QString& content);

bool extractDicoListData(QByteArray& data, QStringList& names);
QByteArray serialiseDicoListData(const QStringList& names);

bool extractRemoveDicoData(QByteArray& data, QString& name);
QByteArray serialiseRemoveDicoData(const QString& name);

bool extractUpdateRessourcesData(QByteArray& data, QMap<QString, RSID>& ressources);
QByteArray serialiseUpdateRessourcesData(const QMap<QString, RSID>& ressources);

bool extractScriptListData(QByteArray& data, QStringList& list);
QByteArray serialiseScriptListData(const QStringList& list);

bool extractSendScriptData(QByteArray& data, QString& name, QString& content);
QByteArray serialiseSendScriptData(const QString& name, const QString& content);

bool extractRequestScriptData(QByteArray& data, QString& name);
QByteArray serialiseRequestScriptData(const QString& name);

bool extractDeleteScriptData(QByteArray& data, QString& name);
QByteArray serialiseDeleteScriptData(const QString& name);

bool extractRenameScriptData(QByteArray& data, QString& name, QString& newName);
QByteArray serialiseRenameScriptData(const QString& name, const QString& newName);

bool extractEntitiesInformationsData(QByteArray& data, QList<EntityInformations>& list);
QByteArray serialiseEntitiesInformationsData(const QList<EntityInformations>& list);

bool extractUpdateEntityInformationsData(QByteArray& data, EntityInformations& info);
QByteArray serialiseUpdateEntityInformationsData(const EntityInformations& info);

bool extractCreateEntityData(QByteArray& data, QString& name, QString& scriptName);
QByteArray serialiseCreateEntityData(const QString& name, const QString& scriptName);

bool extractInjectCodeData(QByteArray& data, QString& entityName, QString& code);
QByteArray serialiseInjectCodeData(const QString& entityName, const QString& code);

bool extractScriptMessageData(QByteArray& data, qint32 &type, QString& ent, QString& txt);
QByteArray serialiseScriptMessageData(qint32 type, const QString& ent, const QString& txt);

bool extractDeleteEntityData(QByteArray& data, QString& name);
QByteArray serialiseDeleteEntityData(const QString& name);

bool extractCharacterListData(QByteArray& data, QStringList& list);
QByteArray serialiseCharacterListData(const QStringList& list);

#endif
