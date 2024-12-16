/* 
 * File:   Player.h
 * Author: anast
 *
 * Created on November 25, 2024, 4:35 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
class Player
{
    private:
        const short SIZE=30;
        Card Hand[30];
        short number;
        short points;
        ~Player();//destructor
    public:
        Player();//constructor
        void setNo(short);
        void setPnts(short);
        short getNo();
        short getPnts();
        void reset();
        
};

Player::Player()
{
    for(int i=0;i<SIZE;i++)
    {
        Hand[i].setFace(" ");
        Hand[i].setSuit(" ");
    }
    number=0;
    points=0;
}
Player::~Player()
{
    
}
void Player::setNo(short n)
{
    number=n;
}
void Player::setPnts(short p)
{
    points=p;
}
short Player::getNo()
{
    return number;
}
short Player::getPnts()
{
    return points;
}
#endif /* PLAYER_H */

