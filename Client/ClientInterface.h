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

    private:
        ClientNetwork* m_network;

        ///Chat GUI
        QTextEdit* m_chat;
        QTextEdit* m_narrator;
        QTextEdit* m_RPChat;

        QWidget* m_mapWi;
};

#endif
