#ifndef EDITORDIALOG_H
#define EDITORDIALOG_H

#include <QDialog>
class QsciScintilla;

class EditorDialog : public QDialog
{
    Q_OBJECT
    public:
        EditorDialog(QWidget* _pa = 0);

        void setText(const QString&);
        void setScriptName(const QString&);

    private:
        QsciScintilla *m_editor;
};

#endif
