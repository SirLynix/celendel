#include "ScriptManager.h"

#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QLineEdit>
#include <QInputDialog>

#include "EditorDialog.h"

ScriptManager::ScriptManager(QWidget* parent):QWidget(parent)
{
    m_editor = new EditorDialog(this);
    connect(m_editor, SIGNAL(sendScriptToServer(QString,QString)), this, SLOT(sendScript(QString,QString)));

    m_download = new QAction(tr("Télécharger"), this);
    connect(m_download, SIGNAL(triggered()), this, SLOT(ac_download()));
    m_makeEntity = new QAction(tr("Nouvelle entitée"), this);
    connect(m_makeEntity, SIGNAL(triggered()), this, SLOT(ac_makeEntity()));
    m_rename = new QAction(tr("Renommer"), this);
    connect(m_rename, SIGNAL(triggered()), this, SLOT(ac_rename()));
    m_delete = new QAction(tr("Supprimer"), this);
    connect(m_delete, SIGNAL(triggered()), this, SLOT(ac_delete()));


    QHBoxLayout* lay = new QHBoxLayout;

    {
    m_list = new QListWidget(this);
    m_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContextMenu(const QPoint&)));
    m_gb = new QGroupBox(tr("Script sur le serveur"), this);

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_list);
    m_gb->setLayout(l);
    }
    lay->addWidget(m_gb);


    m_openEditor = new QPushButton(tr("Ouvrir l'éditeur"), this);
    connect(m_openEditor, SIGNAL(pressed()), this, SLOT(openEditor()));
    lay->addWidget(m_openEditor);

    setLayout(lay);
}

void ScriptManager::openEditor()
{
    m_editor->show();
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
    l<<m_download;
    l<<m_makeEntity;
    l<<m_rename;
    l<<m_delete;

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
    DEB() << "ScriptManager " << name;
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
}

