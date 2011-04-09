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

        void downloadButtonPressed();

    signals:
        void requestScriptDownload(QString name);

    private:
        QStringList m_scripts;

        QListWidget* m_list;
        QPushButton* m_download;
        QGroupBox* m_gb;

        QPushButton* m_openEditor;

        EditorDialog* m_editor;

      /*  QTextEdit* m_edit;
        QLabel* m_editName;
        QGroupBox* m_gbEdit;*/
};

#endif
