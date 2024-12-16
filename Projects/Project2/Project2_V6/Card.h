#ifndef CARD_H
#define CARD_H

#include <cstring>
#include <iostream>
using namespace std;

#include "BCard.h"

class Card: public BCard
{
    private:
        char *face;
        char *suit;
    public:
        Card();//default constructor. face, suit arrays blank by default
        Card(char*,char*);//overloaded constructor
        Card(const Card&);//copy constructor
        void operator=(const Card&);//overloads = operator
        bool operator==(const Card&);//overloads == operator
        bool operator!=(const Card&);//overloads != operator
        void setFace(char *f){strcpy(face,f);}//sets face value to specified char array
        void setSuit(char *s){strcpy(suit,s);}//sets suit to specified char array
        char *getFace(){return face;}//returns face
        char *getSuit(){return suit;}//returns suit
        void dspCard(){cout<<face<<" of "<<suit;}//displays face and suit of specified card
        ~Card(){delete []face;delete []suit;}
};

#endif /* CARD_H */

