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

QString CharactersManager::getCharacterName(const EntityInformations& e)
{
    QString n = e.data.value("name").getString();

    return (n.isEmpty()) ? e.name : n;
}


void CharactersManager::update()
{
    m_list->clear();

    const QList<EntityInformations>& ent = m_entMngr->m_entities;

    for(int i=0, m=ent.size();i<m;++i)
    {
        if(!m_characters.contains(ent[i].name))
            continue;

        QStandardItem *item = new QStandardItem(getCharacterName(ent[i]));
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
        }
    }
}

