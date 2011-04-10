#include "EditorDialog.h"

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>
#include <QLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QInputDialog>
#include <QTextStream>
#include "..\Shared\LuaSystem\ScriptSandbox.h"
#include "..\Shared\LuaSystem\ScriptedEntity.h"

EditorDialog::EditorDialog(QWidget* _pa) : QMainWindow(_pa)
{
    m_editor = new QsciScintilla(this);
	m_editor->setLexer(new QsciLexerLua);
	m_editor->setMarginLineNumbers(1,true);

	{
	    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));

        QAction *ac_save = fileMenu->addAction(tr("&Sauvegarder"));
        ac_save->setWhatsThis(tr("Sauvegarder le script tel qu'il est dans l'éditeur."));
        ac_save->setShortcut(QKeySequence(QKeySequence::Save));
        connect(ac_save, SIGNAL(triggered()), this, SLOT(saveScript()));

        QAction *ac_load = fileMenu->addAction(tr("&Charger"));
        ac_load->setWhatsThis(tr("Charger un script dans l'éditeur."));
        ac_load->setShortcut(QKeySequence(QKeySequence::Open));
        connect(ac_load, SIGNAL(triggered()), this, SLOT(loadScript()));


        QMenu *scriptsMenu = menuBar()->addMenu(tr("&Scripts"));

        QAction *ac_send = scriptsMenu->addAction(tr("&Envoyer au serveur"));
        ac_send->setWhatsThis(tr("Envoyer le script au serveur."));
        connect(ac_send, SIGNAL(triggered()), this, SLOT(sendScript()));

        QAction *ac_run = scriptsMenu->addAction(tr("Lancer le sc&ript"));
        ac_run->setWhatsThis(tr("Executer localement le script, pour détecter les erreurs de syntaxe par exemple."));
        connect(ac_run, SIGNAL(triggered()), this, SLOT(runScript()));

	}

    setCentralWidget(m_editor);

    setScriptName(QString());
}

void EditorDialog::setText(const QString& s)
{
    m_editor->setText(s);
}

void EditorDialog::setScriptName(const QString& s)
{
    if(s.isEmpty())
    {
        setWindowTitle(tr("Aucun script ouvert"));
        return;
    }

    m_name=s;
    setWindowTitle(tr("Script : %1").arg(s));
}

void EditorDialog::sendScript()
{
    QString sn = QInputDialog::getText(this,tr("Nom du script"),tr("Renommer le script ?"),QLineEdit::Normal,m_name);
    if(sn.isEmpty())
        sn = m_name;

    emit sendScriptToServer(sn, m_editor->text());
}

void EditorDialog::saveScript()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Sauvegarder un script"), QString(), tr("Fichiers de script (*.lua);;Tous les fichiers (*.*)"));

    QFile file(name);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder le fichier \"%1\"").arg(name));
        return;
    }
    QTextStream out(&file); out << m_editor->text();
}

void EditorDialog::loadScript()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Charger un script"), QString(), tr("Fichiers de script (*.lua);;Tous les fichiers (*.*)"));
    QFile file(name);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de sauvegarder le fichier \"%1\"").arg(name));
        return;
    }
    setText(file.readAll());


    QString sn = QInputDialog::getText(this,tr("Nom du script"),tr("Entrez un nom pour le script"),QLineEdit::Normal,name);
    if(sn.isEmpty())
        sn = name;

    setScriptName(sn);
}

void EditorDialog::runScript()
{
    ScriptSandbox ssb;
    if(ssb.pushCode(m_editor->text()))
    {
        QMessageBox::warning(this, tr("Erreur dans le script"), tr("Message : \"%1\"").arg(ssb.errorString()));
    }
    else
        QMessageBox::information(this, tr("Script valide"), tr("Il ne semble pas y avoir d'erreur de syntaxe dans le script."));
}
