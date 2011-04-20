#include <QTreeView>
#include <QStandardItemModel>
#include <QLayout>
#include <QHeaderView>
#include <QAction>
#include <QMenu>

#include "EntitiesManager.h"
#include "EditorDialog.h"
#include "../Shared/Serializer.h"

#define DTANAMID Qt::UserRole+1337

QDataStream &operator<<(QDataStream & ds, const EntitiesManager& p)
{
    ds << p.m_entities;
    return ds;
}

QDataStream &operator>>(QDataStream & ds, EntitiesManager& p)
{
    QList<EntityInformations> e;
    ds>>e;
    p.setEntities(e);
    return ds;
}

EntitiesManager::EntitiesManager(QWidget* _parent) : QWidget(_parent)
{
    m_GM = false;

    m_injectCode = new QAction(tr("Injecter du code"), this);
    connect(m_injectCode, SIGNAL(triggered()), this, SLOT(ac_injectCode()));
    m_deleteEntity = new QAction(tr("Supprimer"), this);
    connect(m_deleteEntity, SIGNAL(triggered()), this, SLOT(ac_deleteEntity()));

    m_editor = new EditorDialog(this, CODE_INJECTION);
    m_editor->hide();


    m_list = new QStandardItemModel(this);

    m_v_list = new QTreeView(this);
    m_v_list->setModel(m_list);
    m_v_list->header()->hide();
    m_v_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_v_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_v_list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContextMenu(const QPoint&)));

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(m_v_list);
    setLayout(l);
}

void EntitiesManager::setGM(bool m)
{
    m_GM=m;
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

EntityInformations* EntitiesManager::findEntity(const QString& n)
{
    for(int i=0,m=m_entities.size();i<m;++i)
        if(m_entities[i].name==n)
            return &m_entities[i];
    return NULL;
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

        for(QMap<QString,EntityData>::const_iterator j = m_entities[i].data.constBegin() ; j!=m_entities[i].data.constEnd() ; ++j)
        {
            QStandardItem *sti=new QStandardItem;
            sti->setText( (j.value().shownName.isEmpty()) ? j.key() : j.value().shownName );
            sti->setData(m_entities[i].name, DTANAMID);
            item->appendRow(sti);

            QStandardItem *stec=new QStandardItem;
            stec->setText(tr("Nom en. : \"%1\"").arg(j.key()));
            stec->setData(m_entities[i].name, DTANAMID);
            sti->appendRow(stec);

            if(j.value().isString() || j.value().isNumber())
            {
                QStandardItem *stic=new QStandardItem;
                stic->setText(j.value().getString());
                stic->setData(m_entities[i].name, DTANAMID);
                sti->appendRow(stic);
            }
            else if(j.value().isStringPairList())
            {
                QStringPairList li = j.value().getStringPairList();
                for(int k=0,m=li.size();k<m;++k)
                {
                    QStandardItem *stic=new QStandardItem;
                    stic->setText(li[k].first);
                    stic->setData(m_entities[i].name, DTANAMID);
                    sti->appendRow(stic);

                    QStandardItem *stoc=new QStandardItem;
                    stoc->setText(li[k].second);
                    stoc->setData(m_entities[i].name, DTANAMID);
                    stic->appendRow(stoc);
                }
            }
            else
            {
                QStandardItem *stic=new QStandardItem;
                stic->setText(tr("Erreur : données invalides"));
                stic->setData(m_entities[i].name, DTANAMID);
                sti->appendRow(stic);
            }
        }
    }

    emit updated();
}

void EntitiesManager::entityDeleted(const QString& ent)
{
    for(int i=0, m=m_entities.size();i<m;++i)
    {
        if(m_entities[i].name == ent)
        {
            m_entities.removeAt(i);
            break;
        }
    }

    update();
}

void EntitiesManager::ac_injectCode()
{
    QString s = m_injectCode->data().toString();
    if(s.isEmpty())
        return;

    m_editor->show();
    m_editor->setScriptName(s);
    connect(m_editor, SIGNAL(sendScriptToServer(QString,QString)), this, SIGNAL(injectCode(QString, QString)));
}

void EntitiesManager::ac_deleteEntity()
{
    QString s = m_injectCode->data().toString();
    if(s.isEmpty())
        return;

    emit deleteEntity(s);
}

void EntitiesManager::openContextMenu(const QPoint& p)
{
    QModelIndex m = m_v_list->indexAt(p);
    if(!m.isValid())
        return;
    QString s = m.data(DTANAMID).toString();

    m_injectCode->setData(s);
    m_deleteEntity->setData(s);

    QList<QAction*> l;
    if(isGM())
    {
        l<<m_injectCode;
        l<<m_deleteEntity;
    }

    if(!l.isEmpty())
        QMenu::exec(l, m_v_list->mapToGlobal(p));
}
