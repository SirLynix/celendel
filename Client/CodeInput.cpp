#include "CodeInput.h"

#include "EditorDialog.h"

#include <QLayout>
#include "..\Shared\Constants.h"

CodeInput::CodeInput(QWidget* parent, const QString& caption, const QString& text) : QDialog(parent)
{
    m_editor = new EditorDialog(this);

    m_editor->setText(text);

    setWindowTitle(caption);

	connect(m_editor, SIGNAL(sendScriptToServer(QString,QString)), this, SLOT(accept()));

	QVBoxLayout* vl = new QVBoxLayout;
	vl->addWidget(m_editor);

	setLayout(vl);
}

QString CodeInput::code() const
{
    return m_editor->getText();
}


QString CodeInput::getCode(QWidget* parent, const QString& caption, const QString& text, bool *ok)
{
    bool tzr=false;
    if(ok==0)
        ok=&tzr;

   /* CodeInput w(parent, caption, text);

    *ok=(w.exec()==QDialog::Accepted);*/

    EditorDialog d(parent);
    d.setWindowModality(Qt::WindowModal);
    d.setWindowFlags(Qt::Popup);
    d.setText(text);
    d.setWindowTitle(caption);

    d.show();

    *ok = false;

    DEB() << "Ayayay";

    return d.getText();
}
