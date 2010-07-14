#include "ClientSettings.h"
#include "ClientInterface.h"

QSettings* allocateSettings(QObject* parent)
{
    return new QSettings("Celendel Team", "Celendel", parent);
}

ClientSettings::ClientSettings(ClientInterface* parent)
{
    m_parent = parent;
    setParent(parent);

    setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint);

    m_settings = allocateSettings(this);

    QVBoxLayout* la = new QVBoxLayout;
    setLayout(la);

    {
        QGroupBox *gb = new QGroupBox(tr("Général"));
        la->addWidget(gb);
        QVBoxLayout* v_la = new QVBoxLayout;
        gb->setLayout(v_la);

        {
            QHBoxLayout* h_la = new QHBoxLayout;
            v_la->addLayout(h_la);

            m_nickname = new QLineEdit(m_settings->value(PARAM_NICK).toString(), this);
            m_nickname->setMaxLength(MAX_NICKNAME_LENGHT);
            h_la->addWidget(new QLabel(tr("Pseudo :")));
            h_la->addWidget(m_nickname);
        }

    }

    {
        QGroupBox *gb = new QGroupBox(tr("Interface"));
        la->addWidget(gb);
        QVBoxLayout* v_la = new QVBoxLayout;
        gb->setLayout(v_la);
        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);
        m_selectInterface = new QPushButton("...", this);
        connect(m_selectInterface, SIGNAL(pressed()), this, SLOT(selectInterface()));
        m_interfacePath = new QLineEdit(m_settings->value(PARAM_INTERFACE, DEFAULT_INTERFACE).toString(), this);
        connect(m_interfacePath, SIGNAL(returnPressed()), this, SLOT(openInterface()));
        h_la->addWidget(m_interfacePath);
        h_la->addWidget(m_selectInterface);
        }

        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        m_saveInterface = new QPushButton(tr("Sauvegarder"), this);
        connect(m_saveInterface, SIGNAL(pressed()), this, SLOT(saveInterface()));
        h_la->addWidget(m_saveInterface);

        m_openInterface = new QPushButton(tr("Charger"), this);
        connect(m_openInterface, SIGNAL(pressed()), this, SLOT(openInterface()));
        h_la->addWidget(m_openInterface);
        }
    }

    {
        QGroupBox *gb = new QGroupBox(tr("Thème"));
        la->addWidget(gb);
        QVBoxLayout* v_la = new QVBoxLayout;
        gb->setLayout(v_la);
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);
        m_selectCSS = new QPushButton("...", this);
        connect(m_selectCSS, SIGNAL(pressed()), this, SLOT(selectCSS()));
        m_CSSPath = new QLineEdit(m_settings->value(PARAM_CSS).toString(), this);
        connect(m_CSSPath, SIGNAL(returnPressed()), this, SLOT(openCSS()));
        h_la->addWidget(m_CSSPath);
        h_la->addWidget(m_selectCSS);

        m_openCSS = new QPushButton(tr("Charger"), this);
        connect(m_openCSS, SIGNAL(pressed()), this, SLOT(openCSS()));
        v_la->addWidget(m_openCSS);
    }

    {
        QGroupBox *gb = new QGroupBox(tr("Paramètres de connexion"));
        la->addWidget(gb);
        QVBoxLayout* v_la = new QVBoxLayout;
        gb->setLayout(v_la);

        v_la->addWidget(new QLabel(tr("Addresse IP et port du serveur :")));

        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        m_serverIP = new QLineEdit(m_settings->value(PARAM_IP, SERVER_IP).toString(), this);
        m_serverIP->setInputMask("000.000.000.000;");
        m_serverPort = new QSpinBox(this);
        m_serverPort->setMinimum(1024);
        m_serverPort->setMaximum(65535);
        m_serverPort->setValue(m_settings->value(PARAM_PORT, SERVER_PORT).toInt());
        h_la->addWidget(m_serverIP);
        h_la->addWidget(new QLabel(":"));
        h_la->addWidget(m_serverPort);

        if(parent->isConnected())
            gb->setEnabled(false);
    }

    {
        m_ok = new QPushButton(tr("Valider"), this);
        m_ok->setDefault(true);
        connect(m_ok, SIGNAL(pressed()), this, SLOT(ok()));
        m_cancel = new QPushButton(tr("Annuler"), this);
        connect(m_cancel, SIGNAL(pressed()), this, SLOT(reject()));
        QHBoxLayout* h_la = new QHBoxLayout;
        h_la->addWidget(m_ok);
        h_la->addWidget(m_cancel);
        la->addLayout(h_la);
    }

}

void ClientSettings::selectCSS()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Charger un thème"), QString(), "Fichiers CSS (*.css)");
    if(fileName.isEmpty())
        return;

    m_CSSPath->setText(fileName);
    openCSS();
}

void ClientSettings::openInterface()
{
    QString path=m_interfacePath->text();
    if(path.isEmpty())
    {
        path=DEFAULT_INTERFACE; // Return to default interface
    }
    QFile file (path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    m_parent->restoreState(file.readAll());
}

void ClientSettings::saveInterface()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder l'interface"), QString(), "Fichiers d'interface (*"IEXT")");
    if(fileName.isEmpty())
        return;

    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(m_parent->saveState());

    m_interfacePath->setText(fileName);
}

void ClientSettings::selectInterface()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Charger une interface"), QString(), "Fichiers d'interface (*"IEXT")");
    if(fileName.isEmpty())
        return;

    m_interfacePath->setText(fileName);
    openInterface();
}

void ClientSettings::openCSS()
{
    if(m_CSSPath->text().isEmpty())
    {
        m_parent->setStyleSheet(""); // Return to default CSS
        return;
    }
    QFile file (m_CSSPath->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString css=file.readAll();
    if(css.isEmpty())
        return;
    m_parent->setStyleSheet(css);
}

void ClientSettings::ok()
{
    m_settings->setValue(PARAM_IP, m_serverIP->text());
    m_settings->setValue(PARAM_PORT, m_serverPort->value());
    m_settings->setValue(PARAM_NICK, m_nickname->text());
    m_settings->setValue(PARAM_CSS, m_CSSPath->text());
    m_settings->setValue(PARAM_INTERFACE, m_interfacePath->text());
    accept();
}

QString ClientSettings::ETS(ENUM_TYPE errorCode, const QString& txt)
{
    static QMap<ENUM_TYPE, QString> stringMap;
    static bool first=true;
    if(first)
    {
        stringMap[ALREADY_VOTED]=tr("Vous avez déjà voté !");
        stringMap[GAME_NOT_LAUNCHED]=tr("La partie n'a pas encore été démarée par le Maître du Jeu.");
        stringMap[NOT_GM]=tr("Vous devez être Maître du Jeu pour effectuer cette action.");
        stringMap[INVALID_PACKET]=tr("Un paquet reçu de votre part par le serveur est invalide.");
        stringMap[INVALID_CANAL]=tr("Le canal demandé n'existe pas.");
        stringMap[CLIENT_DOES_NOT_EXIST]=tr("Ce client n'existe pas !");
        stringMap[CLIENTS_LIMIT_REACHED]=tr("La limite forte du nombre de clients connectés silmutanément a été atteinte. Désolé.");
        stringMap[SANCTION_UNKNOWN]=tr("La sanction demandée est inconnue.");
        first=false;
    }

    return stringMap.contains(errorCode) ? stringMap.value(errorCode).arg(txt) : tr("Une erreur inconnue est arrivée.");
}

