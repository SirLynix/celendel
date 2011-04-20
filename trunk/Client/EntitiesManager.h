#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <QWidget>
#include "../Shared/Constants.h"
#include <QDataStream>

#include "CharactersManager.h"

QDataStream &operator<<(QDataStream & ds, const EntitiesManager& p);
QDataStream &operator>>(QDataStream & ds, EntitiesManager& p);


class QTreeView;
class QStandardItemModel;
class QAction;
class EditorDialog;

class EntitiesManager : public QWidget
{
    Q_OBJECT
    public:
        EntitiesManager(QWidget* _parent = 0);

        bool isGM() const { return m_GM; }

    public slots:
        void updateEntity(const EntityInformations& ent);
        void setEntities(const QList<EntityInformations>& entList);

        void entityDeleted(const QString& ent);

        void setGM(bool m);

    private slots:
        void update();

        void openContextMenu(const QPoint&);

        void ac_injectCode();
        void ac_deleteEntity();

    signals:
        void injectCode(QString entity, QString code);
        void deleteEntity(const QString& ent);

        void updated();

    private:

        friend class CharactersManager;

        friend QDataStream &operator<<(QDataStream & ds, const EntitiesManager& p);
        friend QDataStream &operator>>(QDataStream & ds, EntitiesManager& p);


        EntityInformations* findEntity(const QString&);

        bool m_GM;

        EditorDialog *m_editor;

        QTreeView *m_v_list;
        QStandardItemModel *m_list;

        QAction* m_injectCode;
        QAction* m_deleteEntity;

        QList<EntityInformations> m_entities;
};

#endif
