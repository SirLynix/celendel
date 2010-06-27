#include "Player.h"

Player::Player(CLID cID, QObject* parent) : QObject(parent), m_ID(cID)
{
    m_GM=false;
    m_voted=false;
    m_voteCount=0;
}

void Player::promoteGM()
{
    m_GM=true;
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
