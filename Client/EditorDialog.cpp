#include "EditorDialog.h"

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>
#include <QLayout>

EditorDialog::EditorDialog(QWidget* _pa) : QDialog(_pa)
{
    m_editor = new QsciScintilla(this);
	m_editor->setLexer(new QsciLexerLua);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(m_editor);
    setLayout(l);

    setWindowTitle(tr("Aucun script ouvert"));
}

void EditorDialog::setText(const QString& s)
{
    m_editor->setText(s);
}

void EditorDialog::setScriptName(const QString& s)
{
    setWindowTitle(tr("Script : %1").arg(s));
}
