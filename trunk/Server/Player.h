#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "../Shared/Constants.h"

class Player : public QObject
{
    Q_OBJECT
    public:
        Player(CLID cID, QObject* parent=NULL);
        CLID ID() const { return m_ID;}
        quint16 voteCount() const {return m_voteCount;}
        bool isGM() const {return m_GM;}
        bool vote(Player* ply); //Return true if the player already voted.

        QString nickname;

    public slots:
        void promoteGM();
        void voteEnded() {m_voted=true;};

    private:
        CLID m_ID;
        bool m_GM;
        bool m_voted;
        quint16 m_voteCount;
};

#endif // PLAYER_H
