#ifndef EDITORDIALOG_H
#define EDITORDIALOG_H

#include <QMainWindow>

class QsciScintilla;
class QMenu;

enum EDITOR_MODE { STANDARD, SCRIPT_EDIT, CODE_INJECTION };

class EditorDialog : public QMainWindow
{
    Q_OBJECT
    public:
        EditorDialog(QWidget* _pa = 0, EDITOR_MODE mode = STANDARD);

        void setText(const QString&);
        QString getText() const;

        void setScriptName(const QString&);
        QString getScriptName() const { return m_name; }

        void setEditorMode(EDITOR_MODE mode);
        EDITOR_MODE getEditorMode() const { return m_mode; }

    signals:
        void sendScriptToServer(QString name, QString content);

    private slots:

        void saveScript();
        void loadScript();

        void sendScript();

        void runScript();

        void update();

    private:

        EDITOR_MODE m_mode;

        QString m_name;
        QsciScintilla *m_editor;

        QMenu *m_scriptsMenu;
        QAction *ac_send;
};

#endif
