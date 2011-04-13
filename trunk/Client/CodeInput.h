#ifndef CODEINPUT_H
#define CODEINPUT_H

#include <QDialog>

class EditorDialog;
class QPushButton;

class CodeInput : public QDialog
{
    Q_OBJECT
    public:
        CodeInput(QWidget* parent = 0, const QString& caption = QString(), const QString& text = QString());

        QString code() const;

        static QString getCode(QWidget* parent=0, const QString& caption = QString(), const QString& text = QString(), bool *ok=0);

    private:

        EditorDialog *m_editor;
        QPushButton *m_ok;
        QPushButton *m_cancel;

};

#endif
