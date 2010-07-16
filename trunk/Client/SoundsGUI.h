#ifndef DEF_SOUNDSGUI
#define DEF_SOUNDSGUI

#include <QtGui>
#include "..\Shared\Constants.h"

class dial:public QDialog
{
    public:
        dial(QWidget *parent=NULL);
};

class SoundsGUI : public QDialog
{
    Q_OBJECT
    public:
        SoundsGUI(QWidget *parent=NULL);

    private slots:
        void stop();
        void play();
        void contextMenu(const QPoint&);

        void createLib();

    private:
        QPushButton *m_back;
        QPushButton *m_new;
        QStandardItemModel* m_model;
        QTreeView* m_view;

        QAction* m_a_play;
        QAction* m_a_stop;

        dial* d;
};

#endif
