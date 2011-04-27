#include "ClientInterface.h"
#include "../Shared/Serializer.h"

#include "EntitiesManager.h"
#include "ScriptManager.h"


void ClientInterface::buildGMStuff()
{
    m_refreshTimer=new QTimer(this);
    m_refreshTimer->setSingleShot(false);
    m_refreshTimer->start(150);
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    m_needRefresh=true;

    connect(m_narrator, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void ClientInterface::updateGMPanel()
{
    if(isGM())
    {
        m_GMPanelDock->show();
    }
    else
    {
        m_GMPanelDock->hide();
    }
    m_entitiesManager->setGM(isGM());
    m_scriptManager->setGM(isGM());
}

bool ClientInterface::addLanguage()
{
    if(!isGM())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous n'êtes pas Maître du Jeu, ou vous n'êtes connecté à aucun serveur !"));
        return false;
    }
    QString lang = QInputDialog::getText(this, tr("Ajouter un langage"), tr("Nom du langage :")).simplified();
    if(lang.isEmpty())
        return false;
    QString dic = QInputDialog::getText(this, tr("Ajouter un langage"), tr("Dictionnaire à utiliser :")).simplified();
    if(dic.isEmpty())
        return false;

    if(addLanguage(lang, dic))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Ce langage existe déjà !"));
        return false;
    }

    return true;
}

bool ClientInterface::addLanguage(const QString& lang, const QString& dic)
{
    if(!isGM())
        return false;

    QList<QTableWidgetItem *> itLi=m_languageManagement->findItems(lang, Qt::MatchFixedString); bool tmp(m_RPLanguage->findText(lang, Qt::MatchFixedString)!=-1);
    if(tmp) return true;
    if(!itLi.isEmpty())
    {
        for(int i=itLi.size()-1;i>=0;i--)
        {
            if(itLi[i]->column()==0)
                return true;
        }
    }

    int row=m_languageManagement->rowCount(); m_languageManagement->setRowCount(row+1);
    m_languageManagement->setItem(row, 0, new QTableWidgetItem(lang));
    m_languageManagement->setItem(row, 1, new QTableWidgetItem(dic));

    return false;
}

void ClientInterface::languageListMenu(const QPoint& p)
{
    if(!isGM())
        return;

    QTableWidgetItem* dsq=m_languageManagement->itemAt(0,p.y());
    if(dsq==0)
        return;

    QString txt=dsq->text();
    if(txt.isEmpty())
        return;

    QList<QAction*> list;

    m_addLanguageAct->setData(txt);
    m_removeLanguage->setData(txt);

    list << m_removeLanguage;
    list << m_addLanguageAct;

    QMenu::exec(list, m_languageManagement->mapToGlobal(p));
}

void ClientInterface::sendLanguageList()
{
    if(!isGM())
        return;

    QList<QPair<QString, QString> > list;

    for(int i=0,sizei=m_languageManagement->rowCount();i<sizei;++i)
    {
        list.append(qMakePair(m_languageManagement->item(i,0)->text(),m_languageManagement->item(i,1)->text()));
    }

    m_network->send(ETI(LANGUAGES_LIST), serialiseLanguagesData(list));
}

void ClientInterface::removeLanguageMenu()
{
    removeLanguage(m_removeLanguage->data().toString());
}

bool ClientInterface::removeLanguage(const QString& lang)
{
    if(!isGM())
        return true;

    QList<QTableWidgetItem *> list = m_languageManagement->findItems(lang, Qt::MatchFixedString);

    if(list.isEmpty())
        return true;

    for(int i=list.size()-1;i>=0;i--)
    {
        if(list[i]->column()==0)
        {
            m_languageManagement->removeRow(list[i]->row());
        }
    }

    return false;
}

void ClientInterface::importLanguageList()
{
    if(!isGM())
        return;

    QString path=QFileDialog::getOpenFileName(this, tr("Selectionner une liste de langages"), QString(), tr("Fichiers INI (*.ini);; Tous les fichiers (*.*)"));

    if(path.isEmpty())
        return;

    #define TMPPATH "TMPFILEINI"
    if(!QFile::copy(path, TMPPATH))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de copier le fichier temporaire %1 !").arg(TMPPATH));
        return;
    }

    QSettings set(TMPPATH, QSettings::IniFormat);

    QStringList keys=set.allKeys();

    for(int i=0,sizei=keys.size();i<sizei;++i)
    {
        addLanguage(keys[i], set.value(keys[i]).toString());
    }

    QFile::remove(TMPPATH);
    #undef TMPPATH
}


void ClientInterface::syncDictionariesList(QStringList list)
{
    m_dictionnariesList->clear();
    m_dictionnariesList->addItems(list);
}

void ClientInterface::addDictionnary()
{
    if(!isGM())
        return;

    QString name = QInputDialog::getText(this, tr("Ajouter un dictionnaire"), tr("Nom du dictionnaire :")).simplified();
    if(name.isEmpty())
        return;

    QString path = DICTIONARIES_FOLDER_PATH+name+DICTIONARIES_EXTENSION;
    QFile file(path, this);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Dictionnaire \"%1\" non trouvé, ou impossible à ouvrir en écriture !").arg(path));
         return;
    }
    m_network->send(ETI(ADD_DICO), serialiseAddDicoData(name, file.readAll()));
}

void ClientInterface::narrationChanged(QString txt)
{
    if(!isGM())
    {
        m_narrator->setHtml(txt);
        m_narrator->moveCursor(QTextCursor::End);
    }
}

void ClientInterface::refresh()
{
    if(!m_needRefresh || !isGM())
        return;

    QString t (m_narrator->toHtml().isEmpty());

    if(!t.isEmpty())
        m_network->send(ETI(ALL_NARRATION), serialiseAllNarrationData(t));

    m_needRefresh=false;
}

void ClientInterface::textChanged()
{
    m_needRefresh=true;
}
