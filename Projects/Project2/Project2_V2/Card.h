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
        Card();//constructor. face, suit arrays blank by default
        ~Card();//destructor
    public:
        void setFace(char[]);//sets face value to specified char array
        void setSuit(char[]);//sets suit to specified char array
        char *getFace();//returns face value of card
        char *getSuit();//returns suit of card
        void dspCard();//displays face and suit of specified card
};

Card::Card()
{
    size=9;
    face=new char[size];
    suit=new char[size];
    strcpy(face," ");
    strcpy(suit," ");
}
void Card::setFace(char f[])
{
    strcpy(face,f);
}
void Card::setSuit(char s[])
{
    strcpy(suit,s);
}
char *Card::getFace()
{
    return face;
}
char *Card::getSuit()
{
    return suit;
}
void Card::dspCard()
{
    cout<<face<<" of "<<suit;
}
Card::~Card()
{
    delete [] face;
    delete [] suit;
}

#endif /* CARD_H */

