#include "EntitiesManager.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QLayout>
#include <QHeaderView>
#include <QAction>
#include <QMenu>

#include "CodeInput.h"

#define DTANAMID Qt::UserRole+1337

EntitiesManager::EntitiesManager(QWidget* _parent) : QWidget(_parent)
{
    m_injectCode = new QAction(tr("Injecter une portion de code"), this);
    connect(m_injectCode, SIGNAL(triggered()), this, SLOT(ac_injectCode()));

    m_list = new QStandardItemModel(this);

    m_v_list = new QTreeView(this);
    m_v_list->setModel(m_list);
    m_v_list->header()->hide();

    m_v_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_v_list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContextMenu(const QPoint&)));

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(m_v_list);
    setLayout(l);
}

void EntitiesManager::updateEntity(const EntityInformations& ent)
{

    for(int i=0,m=m_entities.size();i<m;++i)
    {
        if(m_entities[i].name==ent.name)
        {
            m_entities[i].data = ent.data;
            update();
            return;
        }
    }
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

void EntitiesManager::ac_injectCode()
{
    QString s = m_injectCode->data().toString();
    if(s.isEmpty())
        return;

    QString code = CodeInput::getCode(this,tr("Injecter du code"),tr("Code à injecter :"));

    if(code.isEmpty())
        return;

    emit injectCode(s, code);
}

void EntitiesManager::openContextMenu(const QPoint& p)
{
    QModelIndex m = m_v_list->indexAt(p);
    if(!m.isValid())
        return;
    QString s = m.data(DTANAMID).toString();

    m_injectCode->setData(s);

    QList<QAction*> l;
    l<<m_injectCode;

    QMenu::exec(l, m_v_list->mapToGlobal(p));
}
