#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include "../Shared/Constants.h"

class QLineEdit;
class QPushButton;
class QVBoxLayout;

class TableLine : public QWidget
{
    Q_OBJECT
    public:
        TableLine(const QString& s1=QString(), const QString& s2=QString(), QWidget* parent=0);

        QStringPair getPair() const;

    signals:
        void suicide();

    private:
        QLineEdit* m_l1;
        QLineEdit* m_l2;

        QPushButton* m_delete;
};

class TableEditor : public QDialog
{
    Q_OBJECT
    public:
        TableEditor(QWidget* parent=0, const QStringPairList& list = QStringPairList());
        QStringPairList getList() const;

        static QStringPairList editList(QWidget* parent=0,const QStringPairList& list = QStringPairList(), bool* ok=0);

    public slots:
        void setList(const QStringPairList& list);

    private slots:

        void deleteLine();
        void addLine(const QString& s1=QString(), const QString& s2=QString());
        void newLine();

    private:

        QList<TableLine*> m_list;
        QVBoxLayout* m_layout;
        QPushButton* m_newLine;
        QPushButton* m_ok;
};

#endif
