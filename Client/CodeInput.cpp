#include "CodeInput.h"

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>

#include <QPushButton>
#include <QLayout>

CodeInput::CodeInput(QWidget* parent, const QString& caption, const QString& text) : QDialog(parent)
{
    m_editor = new QsciScintilla(this);
	m_editor->setLexer(new QsciLexerLua);
	m_editor->setMarginLineNumbers(1,true);

	m_ok = new QPushButton(tr("Ok"), this);
	connect(m_ok, SIGNAL(pressed()), this, SLOT(accept()));
	m_cancel = new QPushButton(tr("Annuler"), this);
	connect(m_cancel, SIGNAL(pressed()), this, SLOT(reject()));

	QVBoxLayout* vl = new QVBoxLayout;
	vl->addWidget(m_editor);

	QHBoxLayout* hl = new QHBoxLayout;
	hl->addWidget(m_ok), hl->addWidget(m_cancel);
	vl->addLayout(hl);

	setLayout(vl);
}

QString CodeInput::code() const
{
    return m_editor->text();
}


QString CodeInput::getCode(QWidget* parent, const QString& caption, const QString& text, bool *ok)
{
    bool tzr=false;
    if(ok==0)
        ok=&tzr;

    CodeInput w(parent, caption, text);

    *ok=(w.exec()==QDialog::Accepted);

    return w.code();
}
