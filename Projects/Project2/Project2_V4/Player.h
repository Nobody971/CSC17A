/* 
 * File:   Player.h
 * Author: anast
 *
 * Created on November 25, 2024, 4:35 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <cstring>
#include "Card.h"
class Player
{
    private:
        const short SIZE=30;
        Card Hand[30];
        short number;
        short points;
    public:
        Player();//constructor
        void setNo(short n){number=n;}
        void setPnts(short p){points=p;}
        void setFace(short index,char f[]){Hand[index].setFace(f);}
        void setSuit(short index, char s[]){Hand[index].setSuit(s);}
        short getNo(){return number;}
        short getPnts(){return points;}
        char *getFace(short index){return Hand[index].getFace();}
        char *getSuit(short index){return Hand[index].getSuit();}
        void reset();
        void dspHnd();
        void insCard(Card&);//inserts specified Card into Hand[]
        ~Player(){};//destructor
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
void Player::reset()
{
    for(int i=0;i<SIZE;i++)
    {
        Hand[i].setFace(" ");
        Hand[i].setSuit(" ");
    }
    number=0;
    points=0;
}
void Player::dspHnd()
{   
    cout<<"-------------------------"<<endl;
    for(int i=0;i<SIZE;i++)
        if(strcmp(Hand[i].getFace()," ")!=0)
        {
            {   //display contents of hand array at index #i
                Hand[i].dspCard();
                cout<<endl;
            }
        }
    cout<<"-------------------------"<<endl;
}
void Player::insCard(Card &C)
{
    //Card.setFace() won't accept Card.getFace as argument, so need temp cstrings to use as arguments
    char tmpFace[9];
    char tmpSuit[9];
    strcpy(tmpFace,C.getFace());
    strcpy(tmpSuit,C.getSuit());
    //if hand array is blank at index 0, set index 0 equal to C
    if(strcmp(Hand[0].getFace()," ")==0){Hand[0].setFace(tmpFace);Hand[0].setSuit(tmpSuit);}
    //otherwise if hand array is blank at index 1, set index 1 equal to drawn card
    else if(strcmp(Hand[1].getFace()," ")==0){Hand[1].setFace(tmpFace);Hand[1].setSuit(tmpSuit);}
    //keep searching for a blank index until one is found
    else if(strcmp(Hand[2].getFace()," ")==0){Hand[2].setFace(tmpFace);Hand[2].setSuit(tmpSuit);}
    else if(strcmp(Hand[3].getFace()," ")==0){Hand[3].setFace(tmpFace);Hand[3].setSuit(tmpSuit);}
    else if(strcmp(Hand[4].getFace()," ")==0){Hand[4].setFace(tmpFace);Hand[4].setSuit(tmpSuit);}
    else if(strcmp(Hand[5].getFace()," ")==0){Hand[5].setFace(tmpFace);Hand[5].setSuit(tmpSuit);}
    else if(strcmp(Hand[6].getFace()," ")==0){Hand[6].setFace(tmpFace);Hand[6].setSuit(tmpSuit);}
    else if(strcmp(Hand[7].getFace()," ")==0){Hand[7].setFace(tmpFace);Hand[7].setSuit(tmpSuit);}
    else if(strcmp(Hand[8].getFace()," ")==0){Hand[8].setFace(tmpFace);Hand[8].setSuit(tmpSuit);}
    else if(strcmp(Hand[9].getFace()," ")==0){Hand[9].setFace(tmpFace);Hand[9].setSuit(tmpSuit);}
    else if(strcmp(Hand[10].getFace()," ")==0){Hand[10].setFace(tmpFace);Hand[10].setSuit(tmpSuit);}
    else if(strcmp(Hand[11].getFace()," ")==0){Hand[11].setFace(tmpFace);Hand[11].setSuit(tmpSuit);}
    else if(strcmp(Hand[12].getFace()," ")==0){Hand[12].setFace(tmpFace);Hand[12].setSuit(tmpSuit);}
    else if(strcmp(Hand[13].getFace()," ")==0){Hand[13].setFace(tmpFace);Hand[13].setSuit(tmpSuit);}
    else if(strcmp(Hand[14].getFace()," ")==0){Hand[14].setFace(tmpFace);Hand[14].setSuit(tmpSuit);}
    else if(strcmp(Hand[15].getFace()," ")==0){Hand[15].setFace(tmpFace);Hand[15].setSuit(tmpSuit);}
    else if(strcmp(Hand[16].getFace()," ")==0){Hand[16].setFace(tmpFace);Hand[16].setSuit(tmpSuit);}
    else if(strcmp(Hand[17].getFace()," ")==0){Hand[17].setFace(tmpFace);Hand[17].setSuit(tmpSuit);}
    else if(strcmp(Hand[18].getFace()," ")==0){Hand[18].setFace(tmpFace);Hand[18].setSuit(tmpSuit);}
    else if(strcmp(Hand[19].getFace()," ")==0){Hand[19].setFace(tmpFace);Hand[19].setSuit(tmpSuit);}
    else if(strcmp(Hand[20].getFace()," ")==0){Hand[20].setFace(tmpFace);Hand[20].setSuit(tmpSuit);}
    else if(strcmp(Hand[21].getFace()," ")==0){Hand[21].setFace(tmpFace);Hand[21].setSuit(tmpSuit);}
    else if(strcmp(Hand[22].getFace()," ")==0){Hand[22].setFace(tmpFace);Hand[22].setSuit(tmpSuit);}
    else if(strcmp(Hand[23].getFace()," ")==0){Hand[23].setFace(tmpFace);Hand[23].setSuit(tmpSuit);}
    else if(strcmp(Hand[24].getFace()," ")==0){Hand[24].setFace(tmpFace);Hand[24].setSuit(tmpSuit);}
    else if(strcmp(Hand[25].getFace()," ")==0){Hand[25].setFace(tmpFace);Hand[25].setSuit(tmpSuit);}
    else if(strcmp(Hand[26].getFace()," ")==0){Hand[26].setFace(tmpFace);Hand[26].setSuit(tmpSuit);}
    else if(strcmp(Hand[27].getFace()," ")==0){Hand[27].setFace(tmpFace);Hand[27].setSuit(tmpSuit);}
    else if(strcmp(Hand[28].getFace()," ")==0){Hand[28].setFace(tmpFace);Hand[28].setSuit(tmpSuit);}
    else if(strcmp(Hand[29].getFace()," ")==0){Hand[29].setFace(tmpFace);Hand[29].setSuit(tmpSuit);}
}
#endif /* PLAYER_H */

