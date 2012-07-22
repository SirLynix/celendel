#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>

#include <QLayout>
#include <QAction>
#include <QMenu>

#include "CharactersManager.h"
#include "EntitiesManager.h"
#include "EquipmentWidget.h"

#define DTANAMID Qt::UserRole+1337

CharactersManager::CharactersManager(EntitiesManager* entMngr, QWidget *par) : QWidget(par), m_entMngr(entMngr)
{
    connect(entMngr, SIGNAL(updated()), this, SLOT(update()));

    m_list = new QStandardItemModel(this);

    m_v_cl = new QTreeView(this);
    m_v_cl->setContextMenuPolicy(Qt::CustomContextMenu);
    m_v_cl->setModel(m_list);
    m_v_cl->header()->hide();
    m_v_cl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_v_cl, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContextMenu(const QPoint&)));
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_v_cl);
    setLayout(l);

    m_stuff=new EquipmentDialog(this);


    m_stuffEdi = new QAction(tr("Afficher l'équipement"), this);
    connect(m_stuffEdi, SIGNAL(triggered()), this, SLOT(ac_stuffEdi()));
}

void CharactersManager::updateCharacterList(const QStringList& list)
{
    m_characters = list;
    update();
}

QString CharactersManager::getName(const EntityInformations& e) const
{
    QString n = e.data.value("name").getString();

    return (n.isEmpty()) ? e.name : n;
}

QString CharactersManager::getPlayerCharacter(const QString& ply) const
{
    return m_chPlyMap.value(ply);
}


void CharactersManager::update()
{
    m_list->clear();
    m_chPlyMap.clear();

    const QList<EntityInformations>& ent = m_entMngr->m_entities;

    for(int i=0, m=ent.size();i<m;++i)
    {
        if(!m_characters.contains(ent[i].name))
            continue;

        QStandardItem *item = new QStandardItem(getName(ent[i]));
        item->setData(ent[i].name, DTANAMID);
        m_list->appendRow(item);
        {
        QStandardItem *sti=new QStandardItem;
        sti->setText(tr("Entitée : %1").arg(ent[i].name));
        sti->setData(ent[i].name, DTANAMID);
        item->appendRow(sti);
        }
        QString ply = ent[i].data.value("player").getString();
        if(!ply.isEmpty())
        {
            QStandardItem *sti=new QStandardItem;
            sti->setText(tr("Joueur : %1").arg(ply));
            sti->setData(ent[i].name, DTANAMID);
            item->appendRow(sti);
            m_chPlyMap[ply] = getName(ent[i]);
        }
        QStringPairList list=ent[i].data.value("inventory").getStringPairList();
        if(!list.isEmpty())
        {
            QStandardItem *inv=new QStandardItem;
            inv->setText(tr("Inventaire :"));
            inv->setData(ent[i].name, DTANAMID);
            for(int j=0,jm=list.size();j<jm;++j)
            {
                EntityInformations* entPtr = m_entMngr->findEntity(list[j].first);
                if(entPtr==NULL)
                    continue;

                QStandardItem *enti=new QStandardItem;
                enti->setText(getName(*entPtr));
                enti->setData(ent[i].name, DTANAMID);
                inv->appendRow(enti);

                QStandardItem *entpl=new QStandardItem;
                entpl->setText(tr("Emplacement : %1").arg(list[j].second));
                entpl->setData(ent[i].name, DTANAMID);
                enti->appendRow(entpl);
            }
            if(inv->hasChildren())
                item->appendRow(inv);
        }
    }
}

void CharactersManager::openContextMenu(const QPoint& p)
{
    QModelIndex m = m_v_cl->indexAt(p);
    if(!m.isValid())
        return;
    QString s = m.data(DTANAMID).toString();

    m_stuffEdi->setData(s);

    QList<QAction*> l;
    l<<m_stuffEdi;

    if(!l.isEmpty())
        QMenu::exec(l, m_v_cl->mapToGlobal(p));
}

void CharactersManager::ac_stuffEdi()
{
    QString ent = m_stuffEdi->data().toString();

    if(ent.isEmpty())
        return;

    for(int i=0,m=m_entMngr->m_entities.size();i<m;++i)
        if(m_entMngr->m_entities[i].name == ent)
        {
            m_stuff->setEntity(m_entMngr->m_entities[i]);
            break;
        }

    m_stuff->show();
}

