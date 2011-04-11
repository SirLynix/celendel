#include "EntitiesManager.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QLayout>
#include <QHeaderView>

#define DTANAMID Qt::UserRole+1337

EntitiesManager::EntitiesManager(QWidget* _parent) : QWidget(_parent)
{
    m_list = new QStandardItemModel(this);

    m_v_list = new QTreeView(this);
    m_v_list->setModel(m_list);
    m_v_list->header()->hide();
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(m_v_list);
    setLayout(l);
}

void EntitiesManager::addEntity(const EntityInformations& ent)
{
    m_entities.append(ent);
    update();
}

void EntitiesManager::setEntities(const QList<EntityInformations>& entList)
{
    m_entities=entList;
    update();
}

void EntitiesManager::update()
{
    m_list->clear();

    for(int i=0, m=m_entities.size();i<m;++i)
    {
        QStandardItem *item = new QStandardItem(m_entities[i].name);
        item->setData(m_entities[i].name, DTANAMID);
        m_list->appendRow(item);

        for(QMap<QString,QString>::const_iterator j = m_entities[i].data.constBegin() ; j!=m_entities[i].data.constEnd() ; ++j)
        {
            QStandardItem *sti=new QStandardItem;
            sti->setText(j.key());
            sti->setData(m_entities[i].name, DTANAMID);
            item->appendRow(sti);

            QStandardItem *stic=new QStandardItem;
            stic->setText(j.value());
            stic->setData(m_entities[i].name, DTANAMID);
            sti->appendRow(stic);
        }
    }
}
