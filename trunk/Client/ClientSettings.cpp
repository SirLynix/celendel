#include "ClientSettings.h"
#include "ClientInterface.h"
#include "SoundManager.h"
#include "VOIP\VOIP.h"

QSettings* allocateSettings(QObject* parent)
{
    return new QSettings("Celendel Team", "Celendel", parent);
}

ClientSettings::ClientSettings(ClientInterface* parent)
{
    m_parent = parent;
    setParent(parent);
    setWhatsThis(tr("Ici, vous pouvez régler bon nombre d'options du logiciel."));

    setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint|Qt::WindowContextHelpButtonHint);

    m_settings = allocateSettings(this);

    QVBoxLayout* la = new QVBoxLayout;
    QVBoxLayout* la2 = new QVBoxLayout;
    QHBoxLayout* hla= new QHBoxLayout;
    setLayout(hla);
    hla->addLayout(la);
    hla->addLayout(la2);

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
            m_nickname->setWhatsThis(tr("Entrez ici le pseudo que vous utiliserez sur le chat. A contrario de la commande /pseudo, ce pseudo sera automatiquement appliqué à chaque connexion."));
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
        m_selectInterface->setWhatsThis(tr("Parcourir le disque dur..."));
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
        m_saveInterface->setWhatsThis(tr("Sauvegarder une interface."));
        connect(m_saveInterface, SIGNAL(pressed()), this, SLOT(saveInterface()));
        h_la->addWidget(m_saveInterface);

        m_openInterface = new QPushButton(tr("Charger"), this);
        m_openInterface->setWhatsThis(tr("Charger l'interface marquée plus haut."));
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
        m_selectCSS->setWhatsThis(tr("Parcourir le disque dur..."));
        connect(m_selectCSS, SIGNAL(pressed()), this, SLOT(selectCSS()));
        m_CSSPath = new QLineEdit(m_settings->value(PARAM_CSS).toString(), this);
        connect(m_CSSPath, SIGNAL(returnPressed()), this, SLOT(openCSS()));
        h_la->addWidget(m_CSSPath);
        h_la->addWidget(m_selectCSS);

        m_openCSS = new QPushButton(tr("Charger"), this);
        m_openCSS->setWhatsThis(tr("Charger la feuille de style indiquée plus haut."));
        connect(m_openCSS, SIGNAL(pressed()), this, SLOT(openCSS()));
        v_la->addWidget(m_openCSS);
    }

    {
        QGroupBox *gb = new QGroupBox(tr("Paramètres de connexion"));
        gb->setWhatsThis(tr("Ces options ne sont disponibles que lorsque vous n'êtes pas connecté à un serveur."));
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
        QGroupBox *gb = new QGroupBox(tr("Paramètres du son"));
        la2->addWidget(gb);
        QVBoxLayout* v_la = new QVBoxLayout;
        gb->setLayout(v_la);

        v_la->addWidget(new QLabel(tr("Volume des sons d'ambiance :")));

        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        m_sound = new QSlider(this);
        m_sound->setMaximum(1000);
        m_sound->setOrientation(Qt::Horizontal);
        m_sound->setValue(static_cast<int>(m_settings->value(PARAM_SOUND, 100.f).toFloat()*10));
        connect(m_sound, SIGNAL(valueChanged(int)), this, SLOT(soundSliderChanged(int)));
        m_soundSpinBox=new QDoubleSpinBox(this);
        m_soundSpinBox->setMaximum(100); m_soundSpinBox->setMinimum(0); m_soundSpinBox->setMaximum(100); m_soundSpinBox->setDecimals(1);
        m_soundSpinBox->setValue(m_settings->value(PARAM_SOUND, 100.f).toFloat());
        connect(m_soundSpinBox, SIGNAL(valueChanged(double)), this, SLOT(soundSpinBoxChanged(double)));
        h_la->addWidget(m_sound);
        h_la->addWidget(m_soundSpinBox);
        }
        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        h_la->addWidget(new QLabel(tr("Périphériques sonore :")));
        m_chb_dvc_out=new QCheckBox(tr("Utiliser le périphérique par défaut"), this);
        v_la->addWidget(m_chb_dvc_out);
        m_cb_dvc_out=new QComboBox(this);
        m_cb_dvc_out->addItems(getOALDevices(true));
        m_cb_dvc_out->setCurrentIndex(m_cb_dvc_out->findText(getOALCurrentDevice(true)));
        h_la->addWidget(m_cb_dvc_out);

        }
        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        h_la->addWidget(new QLabel(tr("Périphériques de capture :")));
        m_chb_dvc_in=new QCheckBox(tr("Utiliser le périphérique par défaut"), this);
        v_la->addWidget(m_chb_dvc_in);
        m_cb_dvc_in=new QComboBox(this);
        m_cb_dvc_in->addItems(getOALDevices(false));
        int ind=m_cb_dvc_in->findText(getOALCurrentDevice(false));
        if(ind==-1)
        {
            QString d=getOALCurrentDevice(false);
            m_cb_dvc_in->addItem(d);
            m_cb_dvc_in->setCurrentIndex(m_cb_dvc_in->findText(d));
        }
        else
            m_cb_dvc_in->setCurrentIndex(ind);

        h_la->addWidget(m_cb_dvc_in);
        }

    }

    {
        m_voip = new QGroupBox(tr("Paramètres de la VOIP"));
        m_voip->setCheckable(true);
        m_voip->setChecked(m_settings->value(PARAM_VOIP_ENABLED, true).toBool());
        la2->addWidget(m_voip);
        QVBoxLayout* v_la = new QVBoxLayout;
        m_voip->setLayout(v_la);

        v_la->addWidget(new QLabel(tr("Volume de la reception :")));

        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        m_VOIPSound = new QSlider(this);
        m_VOIPSound->setMaximum(1000);
        m_VOIPSound->setOrientation(Qt::Horizontal);
        m_VOIPSound->setValue(static_cast<int>(m_settings->value(PARAM_VOIP_SOUND, 100.f).toFloat()*10));
        connect(m_VOIPSound, SIGNAL(valueChanged(int)), this, SLOT(VOIPSoundSliderChanged(int)));
        m_VOIPSoundSpinBox=new QDoubleSpinBox(this);
        m_VOIPSoundSpinBox->setMaximum(100); m_VOIPSoundSpinBox->setMinimum(0); m_VOIPSoundSpinBox->setDecimals(1);
        m_VOIPSoundSpinBox->setValue(m_settings->value(PARAM_VOIP_SOUND, 100.f).toFloat());
        connect(m_VOIPSoundSpinBox, SIGNAL(valueChanged(double)), this, SLOT(VOIPSoundSpinBoxChanged(double)));
        h_la->addWidget(m_VOIPSound);
        h_la->addWidget(m_VOIPSoundSpinBox);
        }

        v_la->addWidget(new QLabel(tr("Qualité de la VOIP (sortant) :")));

        {
        QHBoxLayout* h_la = new QHBoxLayout;
        v_la->addLayout(h_la);

        m_VOIPQuality = new QSlider(this);
        m_VOIPQuality->setMinimum(1); m_VOIPQuality->setMaximum(100);
        m_VOIPQuality->setOrientation(Qt::Horizontal);
        m_VOIPQuality->setValue(static_cast<int>(m_settings->value(PARAM_VOIP_QUALITY, 4).toFloat()*10));
        connect(m_VOIPQuality, SIGNAL(valueChanged(int)), this, SLOT(VOIPQualitySliderChanged(int)));
        h_la->addWidget(new QLabel(tr("Plus rapide")));
        h_la->addWidget(m_VOIPQuality);
        h_la->addWidget(new QLabel(tr("Plus clair")));
        }
    }

    {
        QGroupBox *gb = new QGroupBox(tr("Bibliothèques de sons"));
        la2->addWidget(gb);

        QPushButton* m_libsListRefresh = new QPushButton(tr("Rafraichir"), this);
        connect(m_libsListRefresh, SIGNAL(pressed()), this, SLOT(refreshLibs()));
        QPushButton* m_libsListLoad = new QPushButton(tr("Charger"), this);
        connect(m_libsListLoad, SIGNAL(pressed()), this, SLOT(loadLibs()));

        QScrollArea* m_libsScroll=new QScrollArea(this);
        {
        QVBoxLayout* v = new QVBoxLayout;
        gb->setLayout(v);
        v->addWidget(m_libsListRefresh);
        v->addWidget(m_libsScroll);
        v->addWidget(m_libsListLoad);
        }
        m_libs_la = new QVBoxLayout;
        {
        gar=new QWidget(this);
        m_libsScroll->setWidget(gar);
        gar->setLayout(m_libs_la);
        }


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
    refreshLibs();
}

void ClientSettings::loadLibs()
{
    QStringList l;
    for(int i=0;i<m_libsList.size();++i)
    {
        if(m_libsList[i]->isChecked())
        {
            l<<m_libsList[i]->text();
        }
    }
    sndMngr.setLibList(l);
    m_settings->setValue(PARAM_SOUNDLIBS, sndMngr.loadedLibs());
}

void ClientSettings::refreshLibs()
{
    for(int i=0;i<m_libsList.size();++i)
    {
        m_libs_la->removeWidget(m_libsList[i]);
        delete m_libsList[i];
    }
    m_libsList.clear();

    QDir dir(LIB_FOLDER);
    if(!dir.exists())
    {
        qDebug() << "Error : sounds libs folder ("LIB_FOLDER") not found. Making directory...";
        dir.setPath(".");
        dir.mkpath(LIB_FOLDER);
        return;
    }
    QStringList filters;
    filters << "*"LIB_EXT;
    dir.setNameFilters(filters);
    QStringList fileList = dir.entryList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Readable);

    QStringList l(sndMngr.loadedLibs());

    int biggestw=0; int biggesth=0;
    for(int i=0;i<fileList.size();++i)
    {
        fileList[i]=fileList[i].left(fileList[i].size()-QString(LIB_EXT).size());
        m_libsList.append(new QCheckBox(fileList[i], this));
        if(m_libsList.last()->sizeHint().width()>biggestw)
            biggestw=m_libsList.last()->sizeHint().width();
        if(m_libsList.last()->sizeHint().height()>biggesth)
            biggesth=m_libsList.last()->sizeHint().height();

        m_libsList.last()->setMinimumSize(m_libsList.last()->sizeHint().width(),m_libsList.last()->sizeHint().height());

        m_libs_la->addWidget(m_libsList.last());

        if(l.contains(fileList[i]))
            m_libsList.last()->setChecked(true);
    }

    gar->setMinimumSize(biggestw+10,(biggesth+1)*fileList.size());
}

void ClientSettings::soundSliderChanged(int value)
{
    float v=static_cast<float>(value)/10.f;
    sndMngr.setVolume(v);
    m_soundSpinBox->setValue(v);
}

void ClientSettings::soundSpinBoxChanged(double value)
{
    sndMngr.setVolume(value);
    m_sound->setValue(static_cast<int>(value*10));
}

void ClientSettings::VOIPQualitySliderChanged(int value)
{
    getVOIP().setQuality((float)value/10.f);
}

void ClientSettings::VOIPSoundSliderChanged(int value)
{
    float v=static_cast<float>(value)/10.f;
    getVOIP().setVolume(v);
    m_VOIPSoundSpinBox->setValue(v);
}

void ClientSettings::VOIPSoundSpinBoxChanged(double value)
{
    getVOIP().setVolume(value);
    m_VOIPSound->setValue(static_cast<int>(value*10));
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
    m_settings->setValue(PARAM_SOUND, static_cast<float>(m_sound->value())/10.f);
    m_settings->setValue(PARAM_VOIP_SOUND, static_cast<float>(m_VOIPSound->value())/10.f);
    m_settings->setValue(PARAM_VOIP_QUALITY, (float)m_VOIPQuality->value()/10.f);
    m_settings->setValue(PARAM_SOUNDLIBS, sndMngr.loadedLibs());
    m_settings->setValue(PARAM_VOIP_ENABLED, m_voip->isChecked());
    getVOIP().setEnabled(m_voip->isChecked());

    if(m_chb_dvc_in->isChecked())
    {
        getVOIP().changeCaptureDevice("");
    }
    else
    {
        QString t=m_cb_dvc_in->currentText();
        if(getOALCurrentDevice(false)!=t)
        {
            getVOIP().changeCaptureDevice(t);
        }
    }

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

