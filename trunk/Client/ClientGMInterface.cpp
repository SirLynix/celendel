#include "ClientInterface.h"
#include "..\Shared\Serializer.h"



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
    if(m_GMID==m_ID) // What if the client is disconnected ? Use isGM() ?
    {
        m_GMPanelDock->show();
    }
    else
    {
        m_GMPanelDock->hide();
    }
}

void ClientInterface::addLanguage()
{
    if(!isGM())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous n'êtes pas Maître du Jeu, ou vous n'êtes connecté à aucun serveur !"));
        return;
    }

    QString lang;
    bool con;
    do {
    con=false;
    lang = QInputDialog::getText(this, tr("Ajouter un langage"), tr("Nom du langage :")).simplified();
    if(lang.isEmpty())
        return;

    QList<QTableWidgetItem *> itLi=m_languageManagement->findItems(lang, Qt::MatchFixedString); bool tmp(m_RPLanguage->findText(lang, Qt::MatchFixedString)!=-1);
    if(tmp||!itLi.isEmpty())
    {
        bool f=false;
        if(!tmp)
        {
            for(int i=itLi.size()-1;i>=0;i--)
            {
                if(itLi[i]->column()==0)
                {
                    f=true;
                    break;
                }
            }
        }
        if(f||tmp)
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Ce langage existe déjà !"));
            con=true;
        }
    }

    } while (con);

    QString dic = QInputDialog::getText(this, tr("Ajouter un langage"), tr("Dictionnaire à utiliser :")).simplified();
    if(dic.isEmpty())
        return;

    int row=m_languageManagement->rowCount(); m_languageManagement->setRowCount(row+1);
    m_languageManagement->setItem(row, 0, new QTableWidgetItem(lang));
    m_languageManagement->setItem(row, 1, new QTableWidgetItem(dic));
}

void ClientInterface::importLanguageList()
{

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

    m_network->send(ETI(ALL_NARRATION), serialiseAllNarrationData(m_narrator->toHtml()));

    m_needRefresh=false;
}

void ClientInterface::textChanged()
{
    m_needRefresh=true;
}
