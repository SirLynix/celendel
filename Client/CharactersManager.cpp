#include "CharactersManager.h"

#include "EntitiesManager.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>

#include <QLayout>

CharactersManager::CharactersManager(EntitiesManager* entMngr, QWidget *parent) : QWidget(parent), m_entMngr(entMngr)
{

    connect(entMngr, SIGNAL(updated()), this, SLOT(update()));

    m_list = new QStandardItemModel(this);

    m_v_cl = new QTreeView(this);
    m_v_cl->setContextMenuPolicy(Qt::CustomContextMenu);
    m_v_cl->setModel(m_list);
    m_v_cl->header()->hide();
    m_v_cl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(m_v_cl);
    setLayout(l);
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
        m_list->appendRow(item);
        {
        QStandardItem *sti=new QStandardItem;
        sti->setText(tr("Entitée : %1").arg(ent[i].name));
        item->appendRow(sti);
        }
        QString ply = ent[i].data.value("player").getString();
        if(!ply.isEmpty())
        {
            QStandardItem *sti=new QStandardItem;
            sti->setText(tr("Joueur : %1").arg(ply));
            item->appendRow(sti);
            m_chPlyMap[ply] = getName(ent[i]);
        }
        QStringPairList list=ent[i].data.value("inventory").getStringPairList();
        if(!list.isEmpty())
        {
            QStandardItem *inv=new QStandardItem;
            inv->setText(tr("Inventaire :"));
            for(int j=0,jm=list.size();j<jm;++j)
            {
                EntityInformations* entPtr = m_entMngr->findEntity(list[j].first);
                if(entPtr==NULL)
                    continue;

                QStandardItem *enti=new QStandardItem;
                enti->setText(getName(*entPtr));
                inv->appendRow(enti);

                QStandardItem *entpl=new QStandardItem;
                entpl->setText(tr("Emplacement : %1").arg(list[j].second));
                enti->appendRow(entpl);
            }
            if(inv->hasChildren())
                item->appendRow(inv);
        }
    }
}

