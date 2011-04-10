#ifndef EDITORDIALOG_H
#define EDITORDIALOG_H

#include <QMainWindow>
class QsciScintilla;

class EditorDialog : public QMainWindow
{
    Q_OBJECT
    public:
        EditorDialog(QWidget* _pa = 0);

        void setText(const QString&);
        void setScriptName(const QString&);

    signals:
        void sendScriptToServer(QString name, QString content);

    private slots:

        void saveScript();
        void loadScript();

        void sendScript();

        void runScript();

    private:
        QString m_name;
        QsciScintilla *m_editor;
};

#endif
