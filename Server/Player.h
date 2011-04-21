#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "../Shared/Constants.h"

class Player : public QObject
{
    Q_OBJECT
    public:
        Player(CLID cID, QObject* parent=NULL);
        CLID ID() const;
        quint16 voteCount() const {return m_voteCount;}
        bool isGM() const {return m_GM;}
        bool vote(Player* ply); //Return true if the player already voted.

        bool match(const QString& regexp) const;

        QString nickname;

    public slots:
        void promoteGM();
        void unPromoteGM();
        void voteEnded() {m_voted=true;};

        void reset();


    private:
        CLID m_ID;
        bool m_GM;
        bool m_voted;
        quint16 m_voteCount;
};

#endif // PLAYER_H
