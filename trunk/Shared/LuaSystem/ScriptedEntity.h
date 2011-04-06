#ifndef SCRIPTEDENTITY_H
#define SCRIPTEDENTITY_H

#include <QObject>

#include "luaHeader.h"
#include <QTime>

class QTimer;
class QString;

class ScriptedEntity : public QObject
{
    Q_OBJECT

    public:
        ScriptedEntity(const QString& file);
        ~ScriptedEntity();

        bool isValid() const { return m_valid; }

    public slots:


        void pause();
        void unpause();

        /// From C++ to Lua ///
        /* All this function must have a 'this' first argument in lua */
        void onUpdate(); /* Args : this, elapsedTime / No return / Will be triggered every 'tick' (100ms ?)*/
        void onInit(); /* Args : this / No return / Will be triggered at loading*/
        void onDeath(); /* Args : this / No return / Will be triggered at destruction*/
        int onDamage(int amount, const QString& type, const QString& from); /* Args : this, amount, type, from / Return effective damage */
        void onUse(const QString& user); /* Args : this, user / No return */

        void callSimpleMethod(const QString& name);

    signals:

        void sendGMMsg(QString);
        void sendOwnerMsg(QString);
        void sendMsg(QString);
        void sendPlayerMsg(QString msg,QString regexp);
        void doAction(QString msg);

    private:

        /// From Lua to C++ ///
        int sendMessageToGM(lua_State* L);
        int sendMessageToOwner(lua_State* L);
        int sendMessageToAll(lua_State* L);
        int sendMessageToPlayer(lua_State* L);


        ScriptedEntity(lua_State*) {}

        Lua_State m_state;
        QString m_fileName;

        bool m_valid;

        QTimer* m_updateTimer;
        QTime m_elapsed;

        friend class Lunar<ScriptedEntity>;
        static const char className[];
        static Lunar<ScriptedEntity>::RegType methods[];
};

#endif // SCRIPTEDENTITY_H
