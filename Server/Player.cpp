#include "Player.h"


Player::Player(CLID cID, QObject* par) : QObject(par), m_ID(cID)
{
    reset();
}

CLID Player::ID() const
{
    return m_ID;
}

void Player::promoteGM()
{
    m_GM=true;
    m_voted=true;
}

void Player::reset()
{
    m_GM=false;
    m_voted=false;
    m_voteCount=0;
}

void Player::unPromoteGM()
{
    m_GM=false;
    m_voted=true;
}

bool Player::vote(Player* ply)
{
    if(m_voted)
        return true;

    ply->m_voteCount++;
    m_voted=true;

    return false;
}

bool Player::match(const QString& regexp) const
{
    QRegExp reg (regexp);
    return reg.exactMatch(nickname);
}
