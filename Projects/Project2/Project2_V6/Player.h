#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <cstring>
using namespace std;

class Player
{
    private:
        short max=11;
        char *name;
        const short SIZE=30;
        Card Hand[30];
        short number;
        short points;
    public:
        Player();//constructor
        void setName(char n[]){strcpy(name,n);}
        void setNo(short n){number=n;}
        void setPnts(short p){points=p;}
        void setFace(short index,char f[]){Hand[index].setFace(f);}
        void setSuit(short index, char s[]){Hand[index].setSuit(s);}
        char *getName(){return name;}
        short getNo(){return number;}
        short getPnts(){return points;}
        char *getFace(short index){return Hand[index].getFace();}
        char *getSuit(short index){return Hand[index].getSuit();}
        Card getCard(short index){return Hand[index];}
        void reset();
        void dspHnd();
        void insCard(Card&);//inserts specified Card into Hand[]
        friend void dspPnts(Player[],short,short);
        ~Player(){delete []name;};//destructor
};

#endif /* PLAYER_H */

