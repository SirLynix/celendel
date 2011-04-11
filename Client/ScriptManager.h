#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <QWidget>
#include <QMap>
#include "..\Shared\Constants.h"

class QListWidget;
class QTextEdit;
class QGroupBox;
class QLabel;
class QPushButton;
class QAction;

class EditorDialog;

class ScriptManager : public QWidget
{
    Q_OBJECT
    public:
        ScriptManager(QWidget* parent=NULL);

    public slots:
        void updateScriptList(QStringList list);

        void showScriptText(QString script, QString text);
        void openEditor();

        void sendScript(QString name, QString content);
        void openContextMenu(const QPoint& p);

        void ac_download();
        void ac_rename();
        void ac_delete();
        void ac_makeEntity();

    signals:
        void requestScriptDownload(QString name);

        void sendScriptToServer(QString name, QString content);

        void deleteScript(QString name);
        void renameScript(QString name, QString newName);

        void makeEntity(QString name, QString scriptName);

    private:
        QStringList m_scripts;

        QListWidget* m_list;
        QGroupBox* m_gb;

        QAction* m_download;
        QAction* m_rename;
        QAction* m_delete;
        QAction* m_makeEntity;

        QPushButton* m_openEditor;

        EditorDialog* m_editor;

      /*  QTextEdit* m_edit;
        QLabel* m_editName;
        QGroupBox* m_gbEdit;*/
};

#endif
