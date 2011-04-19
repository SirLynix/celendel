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
class EntityMaker;

class EditorDialog;

class ScriptManager : public QWidget
{
    Q_OBJECT
    public:
        ScriptManager(QWidget* parent=NULL);

        bool isGM() const { return m_GM; }

    public slots:
        void updateScriptList(QStringList list);

        void setGM(bool);

        void showScriptText(QString script, QString text);
        void openEditor();
        void openEntMaker();

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


        EntityMaker *m_entMaker;

        QListWidget* m_list;
        QGroupBox* m_gb;

        QAction* m_download;
        QAction* m_rename;
        QAction* m_delete;
        QAction* m_makeEntity;

        QPushButton* m_openEditor;
        QPushButton* m_openEntMaker;

        EditorDialog* m_editor;

        bool m_GM;
};

#endif
