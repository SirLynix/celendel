#ifndef SCRIPTENVIRONNEMENT_H
#define SCRIPTENVIRONNEMENT_H

#include <QObject>
#include <QMap>
#include "../Shared/Constants.h"

class ScriptedEntity;

class ScriptEnvironnement : public QObject
{
    Q_OBJECT
    public:
        ScriptEnvironnement();

        ~ScriptEnvironnement();

        bool makeEntity(const QString& name, const QString& scriptName); //Create a new scripted entity - return true on error. There cannot be two entities with the same name.

        bool deleteEntity(const QString& name);

        bool entityExists(const QString& name) const { return m_entities.contains(name); }

        QList<EntityInformations> getEntitiesInformations();
        const QStringList& getCharacters() const { return m_characters; }

        EntityInformations getEntityInformations(const QString& name);

        void addCharacter(const QString& ent);
        void removeCharacter(const QString& ent);

        QString pushCode(const QString& entity, const QString& code, bool* ok = 0);

    private slots:
        void dataChanged();

        void s_sendGMMsg(QString);
        void s_sendOwnerMsg(QString);
        void s_sendMsg(QString);
        void s_sendPlayerMsg(QString msg,QString regexp);
        void s_luaError(QString m);

        void s_registerCharacter();

    signals:
        void entityRequireUpdate(const QString& entName);

        void sendGMMsg(QString ent, QString);
        void sendOwnerMsg(QString ent, QString);
        void sendMsg(QString ent, QString);
        void sendPlayerMsg(QString ent, QString msg,QString regexp);

        void luaError(QString ent, QString);

        void characterListUpdated(const QStringList&);

    private:
        QMap<QString, ScriptedEntity*> m_entities;

        QStringList m_characters;
};

#endif // SCRIPTENVIRONNEMENT_H
