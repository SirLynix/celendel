#ifndef DEF_CLIENTINTERFACE
#define DEF_CLIENTINTERFACE

#include <QMainWindow>
#include "ClientNetwork.h"

#include <QtGui>

class ClientInterface : public QMainWindow
{
    Q_OBJECT
    public:
        ClientInterface();

        void ClientInterface::lg(const QString txt, bool time=true, bool html=true);
        QString ClientInterface::getRolePlayName(CLID ID);

    private slots:
        void sendMessage();
        void chat(CLID sender, QString text, ENUM_TYPE canal);
        void changeServerInformations(ServerInformations si);
        void changeClientID(CLID ID);
        void changeClientNickname(CLID ID, QString nick);
        void showError(ENUM_TYPE e, QString txt);

        void changeGameMaster(CLID ID);
        void clientVoted(CLID f, CLID t);

        void connectionEtablished();
        void connectionLost();
        void diceRolled(CLID, quint16);
        void sanctionned(CLID, ENUM_TYPE, QString);

        void rollDice();
        void serverName(QString);
        void gameLaunched();

        void setTitle(const QString& serverName);

        void updatePlayerList();

        void clientJoined(CLID);
        void clientLeft(CLID);

        void updateGMLabel();
        CLID CLIDFromString(const QString& str);


    private:
        ClientNetwork* m_network;
        QString anonym(CLID ID);
        QString anonym2(CLID ID);

        ///Infos
        bool m_gameStarted;
        CLID m_ID;
        CLID m_GMID;
        QString m_location;
        QString m_TOD;
        QString m_serverName;
        QMap<CLID, QString> m_nickMap;


        ///Chat GUI
        QTextEdit* m_chat;
        QTextEdit* m_narrator;
        QTextEdit* m_RPChat;
        QLineEdit* m_chatInput;
        QPushButton* m_rollTheDice;

        QWidget* m_mapWi;

        ///Player list
        QStandardItemModel *m_playerList;
        QLabel *m_GMLabel;
};

#endif