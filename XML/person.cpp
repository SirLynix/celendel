#include "person.h"
#include <QRegExp>

Person::Person(const QString& filename, const QString& name, BEHAVIOR_TYPE bh, const QString& infos)
{
    if(filename != "")
    {
        XMLObject::load(filename);
    }
    else
    {
        m_name = name;
        m_behavior = bh;
        m_infos = infos;
    }
}

bool Person::loadCustomData()
{

}

void Person::synchroniseCustomData(QString&)
{

}


bool Person::matchPatern(const PlayerPatern& patern)
{
    if(patern.human==true&&m_behavior!=BH_PLAYER)
        return false;

    if(!patern.nameRegExp.isEmpty())
    {
        if(!QRegExp(patern.nameRegExp).exactMatch(m_name))
            return false;
    }
    if(!patern.classRegExp.isEmpty())
    {
        if(!QRegExp(patern.classRegExp).exactMatch(m_class))
            return false;
    }

    return true;
}
