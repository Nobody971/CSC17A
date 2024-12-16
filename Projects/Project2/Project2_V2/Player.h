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
        char *getFace(short);
        char *getSuit(short);
        void setFace(short,char*);
        void setSuit(short,char*);
        void dspHnd();
        void insCard(Card&);//inserts specified Card into Hand[]
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
char *Player::getFace(short index)
{
    return Hand[index].getFace();
}
char *Player::getSuit(short)
{
    return Hand[index].getSuit();
}
void Player::setFace(short,char f[])
{
    Hand[index].setFace(f);
}
void Player::setSuit(short index, char s[])
{
    Hand[index].setSuit(s);
}
void Player::dspHnd()
{   
    cout<<"*********************************"<<endl;
    for(int i=0;i<SIZE;i++)
        if(strcmp(Hand[i].getFace()," ")!=0)
        {
            {   //display contents of hand array at index #i
                Hand[i].dspCard();
            }
        }
    cout<<"*********************************"<<endl;
}
void Player::insCard(Card &C)
{
    //if hand array is blank at index 0, set index 0 equal to C
    if (strcmp(Hand[0].getFace()," ")==0&&strcmp(Hand[0].getSuit()," ")==0)
    {Hand[0].setFace(C.getFace());Hand[0].setSuit(C.getSuit);}
    //otherwise if hand array is blank at index 1, set index 1 equal to drawn card
    else if (strcmp(Hand[1].getFace()," ")==0&&strcmp(Hand[1].getSuit()," ")==0)
    {Hand[1].setFace(C.getFace());Hand[1].setSuit(C.getSuit);}
    //keep searching for a blank index until one is found
    else if (strcmp(Hand[2].getFace()," ")==0&&strcmp(Hand[2].getSuit()," ")==0)
    {Hand[2].setFace(C.getFace());Hand[2].setSuit(C.getSuit);}
    else if (strcmp(Hand[3].getFace()," ")==0&&strcmp(Hand[3].getSuit()," ")==0)
    {Hand[3].setFace(C.getFace());Hand[3].setSuit(C.getSuit);}
    else if (strcmp(Hand[4].getFace()," ")==0&&strcmp(Hand[4].getSuit()," ")==0)
    {Hand[4].setFace(C.getFace());Hand[4].setSuit(C.getSuit);}
    else if (strcmp(Hand[5].getFace()," ")==0&&strcmp(Hand[5].getSuit()," ")==0)
    {Hand[5].setFace(C.getFace());Hand[5].setSuit(C.getSuit);}
    else if (strcmp(Hand[6].getFace()," ")==0&&strcmp(Hand[6].getSuit()," ")==0)
    {Hand[6].setFace(C.getFace());Hand[6].setSuit(C.getSuit);}
    else if (strcmp(Hand[7].getFace()," ")==0&&strcmp(Hand[7].getSuit()," ")==0)
    {Hand[7].setFace(C.getFace());Hand[7].setSuit(C.getSuit);}
    else if (strcmp(Hand[8].getFace()," ")==0&&strcmp(Hand[8].getSuit()," ")==0)
    {Hand[8].setFace(C.getFace());Hand[8].setSuit(C.getSuit);}
    else if (strcmp(Hand[9].getFace()," ")==0&&strcmp(Hand[9].getSuit()," ")==0)
    {Hand[9].setFace(C.getFace());Hand[9].setSuit(C.getSuit);}
    else if (strcmp(Hand[10].getFace()," ")==0&&strcmp(Hand[10].getSuit()," ")==0)
    {Hand[10].setFace(C.getFace());Hand[10].setSuit(C.getSuit);}
    else if (strcmp(Hand[11].getFace()," ")==0&&strcmp(Hand[11].getSuit()," ")==0)
    {Hand[11].setFace(C.getFace());Hand[11].setSuit(C.getSuit);}
    else if (strcmp(Hand[12].getFace()," ")==0&&strcmp(Hand[12].getSuit()," ")==0)
    {Hand[12].setFace(C.getFace());Hand[12].setSuit(C.getSuit);}
    else if (strcmp(Hand[13].getFace()," ")==0&&strcmp(Hand[13].getSuit()," ")==0)
    {Hand[13].setFace(C.getFace());Hand[13].setSuit(C.getSuit);}
    else if (strcmp(Hand[14].getFace()," ")==0&&strcmp(Hand[14].getSuit()," ")==0)
    {Hand[14].setFace(C.getFace());Hand[14].setSuit(C.getSuit);}
    else if (strcmp(Hand[15].getFace()," ")==0&&strcmp(Hand[15].getSuit()," ")==0)
    {Hand[15].setFace(C.getFace());Hand[15].setSuit(C.getSuit);}
    else if (strcmp(Hand[16].getFace()," ")==0&&strcmp(Hand[16].getSuit()," ")==0)
    {Hand[16].setFace(C.getFace());Hand[16].setSuit(C.getSuit);}
    else if (strcmp(Hand[17].getFace()," ")==0&&strcmp(Hand[17].getSuit()," ")==0)
    {Hand[17].setFace(C.getFace());Hand[17].setSuit(C.getSuit);}
    else if (strcmp(Hand[18].getFace()," ")==0&&strcmp(Hand[18].getSuit()," ")==0)
    {Hand[18].setFace(C.getFace());Hand[18].setSuit(C.getSuit);}
    else if (strcmp(Hand[19].getFace()," ")==0&&strcmp(Hand[19].getSuit()," ")==0)
    {Hand[19].setFace(C.getFace());Hand[19].setSuit(C.getSuit);}
    else if (strcmp(Hand[20].getFace()," ")==0&&strcmp(Hand[20].getSuit()," ")==0)
    {Hand[20].setFace(C.getFace());Hand[20].setSuit(C.getSuit);}
    else if (strcmp(Hand[21].getFace()," ")==0&&strcmp(Hand[21].getSuit()," ")==0)
    {Hand[21].setFace(C.getFace());Hand[21].setSuit(C.getSuit);}
    else if (strcmp(Hand[22].getFace()," ")==0&&strcmp(Hand[22].getSuit()," ")==0)
    {Hand[22].setFace(C.getFace());Hand[22].setSuit(C.getSuit);}
    else if (strcmp(Hand[23].getFace()," ")==0&&strcmp(Hand[23].getSuit()," ")==0)
    {Hand[23].setFace(C.getFace());Hand[23].setSuit(C.getSuit);}
    else if (strcmp(Hand[24].getFace()," ")==0&&strcmp(Hand[24].getSuit()," ")==0)
    {Hand[24].setFace(C.getFace());Hand[24].setSuit(C.getSuit);}
    else if (strcmp(Hand[25].getFace()," ")==0&&strcmp(Hand[25].getSuit()," ")==0)
    {Hand[25].setFace(C.getFace());Hand[25].setSuit(C.getSuit);}
    else if (strcmp(Hand[26].getFace()," ")==0&&strcmp(Hand[26].getSuit()," ")==0)
    {Hand[26].setFace(C.getFace());Hand[26].setSuit(C.getSuit);}
    else if (strcmp(Hand[27].getFace()," ")==0&&strcmp(Hand[27].getSuit()," ")==0)
    {Hand[27].setFace(C.getFace());Hand[27].setSuit(C.getSuit);}
    else if (strcmp(Hand[28].getFace()," ")==0&&strcmp(Hand[28].getSuit()," ")==0)
    {Hand[28].setFace(C.getFace());Hand[28].setSuit(C.getSuit);}
    else if (strcmp(Hand[29].getFace()," ")==0&&strcmp(Hand[29].getSuit()," ")==0)
    {Hand[29].setFace(C.getFace());Hand[29].setSuit(C.getSuit);}
}
#endif /* PLAYER_H */

