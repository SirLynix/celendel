#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <QWidget>
#include "..\Shared\Constants.h"

class QTreeView;
class QStandardItemModel;

class EntitiesManager : public QWidget
{
    Q_OBJECT
    public:
        EntitiesManager(QWidget* _parent = 0);

    public slots:
        void addEntity(const EntityInformations& ent);
        void setEntities(const QList<EntityInformations>& entList);

    private slots:
        void update();

    private:

        QTreeView *m_v_list;
        QStandardItemModel *m_list;

        QList<EntityInformations> m_entities;
};

#endif
