#ifndef SCRIPTEDENTITY_H
#define SCRIPTEDENTITY_H

#include <QObject>

#include "luaHeader.h"
#include "../Constants.h"
#include <QTime>
#include <QMap>

#define MAX_EXEC_TIME 50

class QTimer;
class QString;

#define LUA_ERROR(a) emit luaError(a)

class ScriptedEntity : public QObject
{
    Q_OBJECT

    public:
        ScriptedEntity(const QString& file = "");
        ~ScriptedEntity();

        bool isValid() const { return m_valid; }

        QString pushCode(const QString& code, bool* ok = 0);

        QStringList getDataKeys();
        QMap<QString, QString> getDataPairs();
        QMap<QString, EntityData> getData();

        QString getName() { return getStr("name"); }
        QString getDescription() { return getStr("description"); }
        QString getType() { return getStr("type"); }
        QString getOwner(){ return getStr("owner");}
        QString getStr(const QString& name, bool* ok = 0);

        QVariant getListStrOrNum(const QString& name, bool* b=0); //Return a QString, a double or a QStringPairList

        double getWeight() { return getNumber("weight"); }
        double getNumber(const QString& name, bool*ok = 0);

        QList<QPair<QString, int> > getLanguages();

        bool dataExist(const QString& name);

    public slots:


        void pause();
        void unpause();

        /// From C++ to Lua ///
        /* All this function must have 'this' as first argument in lua */
        void onUpdate(); /* Args : this, elapsedTime / No return / Will be triggered every 'tick' (1s ?)*/
        void onInit(); /* Args : this / No return / Will be triggered at loading*/
        void onDeath(); /* Args : this / No return / Will be triggered at destruction*/
        int onDamage(int amount, const QString& type, const QString& from); /* Args : this, amount, type, from / Return effective damage */
        void onUse(const QString& user); /* Args : this, user / No return */

        void callSimpleMethod(const QString& name);
        void once();

        void hook(lua_State *L, lua_Debug *ar);

    signals:

        void sendGMMsg(QString);
        void sendOwnerMsg(QString);
        void sendMsg(QString);
        void sendPlayerMsg(QString msg,QString regexp);

        void registerCharacter(QString);

        void dataChanged();

        void luaError(QString txt);

    private:

        /// From Lua to C++ ///
        int sendMessageToGM(lua_State* L);
        int sendMessageToOwner(lua_State* L);
        int sendMessageToAll(lua_State* L);
        int sendMessageToPlayer(lua_State* L);
        int registerAsCharacter(lua_State* L);

        int syncData(lua_State* L);

        ScriptedEntity(lua_State*) {}

        Lua_State m_state;
        QString m_fileName;

        bool m_valid;

        bool m_needSync;

        bool m_showUpdateError;

        QTimer* m_updateTimer;
        QTime m_elapsed;

        QTime m_tempusFugit;

        friend class Lunar<ScriptedEntity>;
        static const char className[];
        static Lunar<ScriptedEntity>::RegType methods[];

        friend void luaHook(lua_State *L, lua_Debug *ar);
};

#endif // SCRIPTEDENTITY_H
