#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QAction>
#include <QLineEdit>
#include <QInputDialog>
#include <QMenu>

#include "ScriptManager.h"
#include "EntityMaker.h"
#include "EditorDialog.h"


ScriptManager::ScriptManager(QWidget* parent):QWidget(parent)
{
    m_GM = false;
    m_editor = new EditorDialog(this, SCRIPT_EDIT);
    connect(m_editor, SIGNAL(sendScriptToServer(QString,QString)), this, SLOT(sendScript(QString,QString)));


    m_entMaker = new EntityMaker(this);
    m_entMaker->hide();
    connect(m_entMaker, SIGNAL(sendScript(QString,QString)), this, SLOT(sendScript(QString,QString)));

    m_download = new QAction(tr("Télécharger"), this);
    connect(m_download, SIGNAL(triggered()), this, SLOT(ac_download()));
    m_makeEntity = new QAction(tr("Nouvelle entitée"), this);
    connect(m_makeEntity, SIGNAL(triggered()), this, SLOT(ac_makeEntity()));
    m_rename = new QAction(tr("Renommer"), this);
    connect(m_rename, SIGNAL(triggered()), this, SLOT(ac_rename()));
    m_delete = new QAction(tr("Supprimer"), this);
    connect(m_delete, SIGNAL(triggered()), this, SLOT(ac_delete()));


    QVBoxLayout* lay = new QVBoxLayout;

    {
    m_list = new QListWidget(this);
    m_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContextMenu(const QPoint&)));
    m_gb = new QGroupBox(tr("Scripts sur le serveur"), this);

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_list);
    m_gb->setLayout(l);
    }
    lay->addWidget(m_gb);

    {
    QHBoxLayout* hl = new QHBoxLayout;
    m_openEditor = new QPushButton(tr("Ouvrir l'éditeur"), this);
    connect(m_openEditor, SIGNAL(pressed()), this, SLOT(openEditor()));
    hl->addWidget(m_openEditor);
    m_openEntMaker = new QPushButton(tr("Ouvrir l'éditeur d'entitées"), this);
    connect(m_openEntMaker, SIGNAL(pressed()), this, SLOT(openEntMaker()));
    hl->addWidget(m_openEntMaker);
    lay->addLayout(hl);
    }


    setLayout(lay);
}

void ScriptManager::openEntMaker()
{
    m_entMaker->show();
}

void ScriptManager::openEditor()
{
    m_editor->show();
}

void ScriptManager::setGM(bool m)
{
    m_GM = m;

    QWidget *p = qobject_cast<QWidget*>(parent());

    if(p == 0)
        p = this;

    if(isGM())
    {
        p->show();

    }
    else
        p->hide();
}

void ScriptManager::openContextMenu(const QPoint& p)
{
    QModelIndex m = m_list->indexAt(p);
    if(!m.isValid())
        return;
    QString s = m.data().toString();

    m_download->setData(s);
    m_rename->setData(s);
    m_delete->setData(s);

    QList<QAction*> l;
    if(isGM())
    {
        l<<m_download;
        l<<m_makeEntity;
        l<<m_rename;
        l<<m_delete;
    }

    if(!l.isEmpty())
        QMenu::exec(l, m_list->mapToGlobal(p));
}

void ScriptManager::ac_download()
{
    QString s = m_download->data().toString();
    if(s.isEmpty())
        return;

    emit requestScriptDownload(s);
}

void ScriptManager::ac_rename()
{
    QString s = m_rename->data().toString();
    if(s.isEmpty())
        return;

    QString newName = QInputDialog::getText(this,tr("Nom du script"),tr("Nouveau nom :"));

    if(newName.isEmpty() || newName==s)
        return;

    emit renameScript(s, newName);
}

void ScriptManager::ac_delete()
{
    QString s = m_delete->data().toString();
    if(s.isEmpty())
        return;
    emit deleteScript(s);
}

void ScriptManager::ac_makeEntity()
{
    QString s = m_delete->data().toString();
    if(s.isEmpty())
        return;

    QString name = QInputDialog::getText(this,tr("Nouvelle entitée"),tr("Nom (unique) de l'entitée :"));

    if(name.isEmpty())
        return;

    emit makeEntity(name, s);
}

void ScriptManager::sendScript(QString name, QString content)
{
    emit sendScriptToServer(name, content);
}

void ScriptManager::updateScriptList(QStringList list)
{
    m_scripts=list;
    m_list->clear();
    m_list->addItems(m_scripts);
}

void ScriptManager::showScriptText(QString script, QString text)
{
    m_editor->setText(text); m_editor->setScriptName(script);
    m_entMaker->setScript(text); m_entMaker->setScriptName(script);
}

