/* 
 * File:   Card.h
 * Author: anast
 *
 * Created on November 25, 2024, 12:40 PM
 */

#ifndef CARD_H
#define CARD_H

#include <cstring>
#include <iostream>
using namespace std;

class Card
{
    private:
        char *face;
        char *suit;
        short size;
    public:
        Card();//constructor. face, suit arrays blank by default
        void setFace(char *f){strcpy(face,f);}//sets face value to specified char array
        void setSuit(char *s){strcpy(suit,s);}//sets suit to specified char array
        char *getFace(){return face;}//returns face
        char *getSuit(){return suit;}//returns suit
        short getSize(){return size;}//returns size
        void dspCard(){cout<<face<<" of "<<suit;}//displays face and suit of specified card
        ~Card();//destructor
};

Card::Card()
{
    size=9;
    face=new char[size];
    suit=new char[size];
    strcpy(face," ");
    strcpy(suit," ");
}
Card::~Card()
{
    delete [] face;
    delete [] suit;
}

#endif /* CARD_H */

