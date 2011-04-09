#include "ScriptManager.h"

#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "EditorDialog.h"

ScriptManager::ScriptManager(QWidget* parent):QWidget(parent)
{
    m_editor = new EditorDialog(this);

    QHBoxLayout* lay = new QHBoxLayout;

    {
    m_list = new QListWidget(this);
    m_download = new QPushButton(tr("Télécharger le script"), this);
    connect(m_download, SIGNAL(pressed()), this, SLOT(downloadButtonPressed()));
    m_gb = new QGroupBox(tr("Script sur le serveur"), this);

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_list); l->addWidget(m_download);
    m_gb->setLayout(l);
    }
    lay->addWidget(m_gb);

 /*   {
    m_edit = new QTextEdit(this);
    m_editName = new QLabel(this);
    m_gbEdit = new QGroupBox(tr("Editer le script"), this);

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_editName); l-> addWidget(m_edit);
    m_gbEdit->setLayout(l);
    }
    lay->addWidget(m_gbEdit);*/

    m_openEditor = new QPushButton(tr("Ouvrir l'éditeur"), this);
    connect(m_openEditor, SIGNAL(pressed()), this, SLOT(openEditor()));
    lay->addWidget(m_openEditor);

    setLayout(lay);
}

void ScriptManager::openEditor()
{
    m_editor->show();
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

void ScriptManager::downloadButtonPressed()
{
    QString name = m_list->currentItem()->text();

    if(!name.isEmpty())
        emit requestScriptDownload(name);
}
