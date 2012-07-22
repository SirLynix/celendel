#ifndef SERVER_H
#define SERVER_H

                    /// The main server class ///
 /*  It rules the game. It receive data from the network class, */
/* Works on it, then answer with the network class once again. */


#include "Network.h"
#include <QList>
#include "Player.h"
#include "../Shared/MapStructs.h"
#include "Translator.h"
#include "ScriptEnvironnement.h"

#define MOTD_DEFAULT_PATH "MOTD.html"

#define SCRIPT_EXT "*.lua"

#define SCRIPTS_ROOT_DIR "Scripts/"
#define SCRIPTS_TEMPLATES_DIR SCRIPTS_ROOT_DIR"Templates/"

#define AUTOCLOSE_DELAY 1000*60*3 //3 mins


class Server : public QObject
{
    Q_OBJECT
    public:
        Server(QObject* parent=NULL);
        ~Server();

        Player* getPlayer(CLID cID);

        bool gameStarted() const {return m_gameStarted;}

        QString narration;
        QString serverName;
        QString location;
        QString timeOfDay;
        QString motd;

        bool changeGM(CLID cID); // Returns true on error

        static QStringList getScriptList();
        static bool isValidScriptName(const QString& name);
        static bool mkscriptpath(const QString& scriptName);

        ServerInformations getServerInformations() const;

        static QString getScriptFolder();

        CLID nickToCLID(const QString& nick);

        QList<CLID> getMatchingPlayers(const QString& regexp);

        QString translateText(const QString& text, const QString& language, CLID cID);

    public slots:
        void addClient(CLID cID);
        void removeClient(CLID cID);
        void launchGame();

        void sendScriptList(CLID cID);

        void sendLuaError(QString ent, QString m);

        bool updateScript(QString name, const QString& content);

        void updateCharacterList(const QStringList&);
        void sendEntityInfos(const QString& name);
        void sendGMMsg(QString ent, QString);
        void sendMsg(QString ent, QString);
        void sendPlayerMsg(QString ent, QString msg,QString regexp);

    private slots:
        void cleanUp();
        void processData(std::auto_ptr<Packet>, CLID);

        void autoClose();

    private:
        ServerNetwork *m_network;
        QList<Player*> m_players;

        QTimer *m_autoClose;


        bool m_gameStarted;

        Translator m_translator;

        QList<SoundLibInformations> m_soundLibs;

        CLID m_GMID;

        MapInformations* m_map;

        QMap<QString, RSID> m_ressources;

        ScriptEnvironnement m_scripts;

};

#endif // SERVER_H
