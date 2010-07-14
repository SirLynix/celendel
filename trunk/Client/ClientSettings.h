#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QtGui>
#include "..\Shared\Constants.h"
class ClientInterface;

QSettings* allocateSettings(QObject* parent=0);

#define PARAM_IP "settings/serverip"
#define PARAM_PORT "settings/serverport"
#define PARAM_NICK "settings/nickname"
#define PARAM_CSS "settings/css"
#define PARAM_INTERFACE "settings/interface"

#define IEXT ".itr"

#define DEFAULT_INTERFACE "default"IEXT

class ClientSettings : public QDialog
{
    Q_OBJECT
    public:
        ClientSettings(ClientInterface* parent);

        static QString ETS(ENUM_TYPE errorCode, const QString& txt);
        //ETS means Error To String. Convert error code to a readable translated QString

    private slots:
        void ok();
        void openCSS();
        void selectCSS();
        void openInterface();
        void selectInterface();
        void saveInterface();

    private:
        QSettings* m_settings;

        QLineEdit* m_serverIP;
        QSpinBox* m_serverPort;

        QLineEdit* m_nickname;

        QPushButton* m_ok;
        QPushButton* m_cancel;

        QPushButton* m_saveInterface;
        QPushButton* m_openInterface;
        QPushButton* m_selectInterface;
        QLineEdit* m_interfacePath;

        QPushButton* m_openCSS;
        QPushButton* m_selectCSS;
        QLineEdit* m_CSSPath;

        ClientInterface* m_parent;
};

#define ETS(a,b) ClientSettings::ETS(a,b)

#endif // CLIENTSETTINGS_H
