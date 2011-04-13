#ifndef CHARACTERSMANAGER_H
#define CHARACTERSMANAGER_H

#include <QWidget>
#include <QStringList>

class EntitiesManager;
class QTreeView;
class QStandardItemModel;
class EntityInformations;

class CharactersManager : public QWidget
{
    Q_OBJECT

    public:
        CharactersManager(EntitiesManager* entMngr, QWidget *parent = 0);

    public slots:
        void updateCharacterList(const QStringList& list);

        QString getCharacterName(const EntityInformations& e);

    private slots:
        void update();

    private:
        EntitiesManager* m_entMngr;

        QStringList m_characters;

        QTreeView *m_v_cl;
        QStandardItemModel *m_list;
};

#endif
