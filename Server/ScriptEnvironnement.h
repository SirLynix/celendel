#ifndef SCRIPTENVIRONNEMENT_H
#define SCRIPTENVIRONNEMENT_H

#include <QObject>
#include <QMap>
#include "..\Shared\Constants.h"

class ScriptedEntity;

class ScriptEnvironnement : public QObject
{
    public:
        ScriptEnvironnement();

        ~ScriptEnvironnement();

        bool makeEntity(const QString& name, const QString& scriptName); //Create a new scripted entity - return true on error. There cannot be two entities with the same name.

        bool entityExists(const QString& name) const { return m_entities.contains(name); }

        QList<EntityInformations> getEntitiesInformations();

        QString pushCode(const QString& entity, const QString& code, bool* ok = 0);

    private:
        QMap<QString, ScriptedEntity*> m_entities;
};

#endif // SCRIPTENVIRONNEMENT_H
