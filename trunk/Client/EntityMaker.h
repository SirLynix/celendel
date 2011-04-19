#ifndef ENTITYMAKER_H
#define ENTITYMAKER_H

#include <QDialog>

#include "../Shared/Constants.h"

class ScriptedEntity;
class QVBoxLayout;
class QLineEdit;
class QDoubleSpinBox;
class QPushButton;
class QComboBox;
class QsciScintilla;

class Line : public QWidget
{
    Q_OBJECT
    public:
        Line(QWidget* parent=0);

        void setName(const QString&);
        void setShownName(const QString&);

        void setData(const QString&);
        void setData(double);
        void setData(const QStringPairList&);

        QString toScript() const;

    private slots:
        void cbChngd(int);
        void tableEditor();

    signals:
        void suicide();

    private:
        QLineEdit* m_name;
        QLineEdit* m_shownName;

        QComboBox* m_comboBox;

        QPushButton* m_delete;

        QDoubleSpinBox* m_number;
        QLineEdit* m_string;
        QPushButton* m_editList;

        QStringPairList m_list;

        bool m_b;
};

class EntityMaker : public QDialog
{
    Q_OBJECT
    public:
        EntityMaker(QWidget* parent=0);

        QString getScriptName() const;
        void setScriptName(const QString&);
        QString getScript() const;
        void setScript(const QString&);

    private slots:
        void addLine(const QString& name, const EntityData& ent);

        void newLine();
        void deleteLine();

        void toEdi();
        void fromEdi();

        void sndScrpt();

    signals:

        void sendScript(const QString& name, const QString& script);

    private:
        QVBoxLayout* m_layout;

        QList<Line*> m_lines;

        QPushButton* m_newLine;

        QLineEdit* m_scriptName;
        QPushButton* m_sendScript;

        QPushButton* m_toEdi;
        QPushButton* m_fromEdi;

        QsciScintilla *m_editor;
};

#endif
