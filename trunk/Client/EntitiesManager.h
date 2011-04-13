#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <QWidget>
#include "..\Shared\Constants.h"

class QTreeView;
class QStandardItemModel;
class QAction;

class EntitiesManager : public QWidget
{
    Q_OBJECT
    public:
        EntitiesManager(QWidget* _parent = 0);

    public slots:
        void updateEntity(const EntityInformations& ent);
        void setEntities(const QList<EntityInformations>& entList);

    private slots:
        void update();

        void openContextMenu(const QPoint&);

        void ac_injectCode();

    signals:
        void injectCode(QString entity, QString code);

    private:

        QTreeView *m_v_list;
        QStandardItemModel *m_list;

        QAction* m_injectCode;

        QList<EntityInformations> m_entities;
};

#endif
