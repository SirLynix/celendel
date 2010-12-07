#ifndef DEF_MATERIALTHING
#define DEF_MATERIALTHING

#include "XMLObject.h"


class MaterialThing : public XMLObject
{
    Q_OBJECT

    public:
    MaterialThing(const QString& filename="");
    uint life() const {return m_life;}
    bool isDestroyable() const {return m_destroyable;}
    bool isDestroyed() const {return m_life==0;}
    void damage(uint dmg);

    protected:

    virtual bool loadCustomData();
    virtual void synchroniseCustomData(QString&);

    bool doAction(const Event& e, bool randomFactor=true);

    unsigned int m_mass;
    uint m_life;
    bool m_destroyable;


};

#endif // DEF_MATERIALTHING
