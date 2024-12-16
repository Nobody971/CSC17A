/* 
 * File:   Deck.h
 * Author: anast
 *
 * Created on November 25, 2024, 2:41 PM
 */

#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <ctime>
#include <cstring>

class Deck
{
    private:
        Card Cards[52];
        const int NCARDS=52;
        Deck();
        ~Deck();
    public:
        void getCard(short);
};

Deck::Deck()
{
    int random;//for storing randomly generated number
    int vC[NCARDS];//to hold shuffled numbers
    Card TmpDeck[NCARDS];//unshuffled deck
    
    //CREATE THE DECK OF CARDS
    //assign first 13 cards to spades
    for(int i=0;i<13;i++)
    {
        TmpDeck[i].setSuit("Spades");
    }
    //assign next 13 cards to clubs
    for(int i=13;i<26;i++)
    {
        TmpDeck[i].setSuit("Clubs");
    }
    //assign next 13 to hearts
    for(int i=26;i<39;i++)
    {
        TmpDeck[i].setSuit("Hearts");
    }
    //assign final 13 to diamonds
    for(int i=39;i<52;i++)
    {
        TmpDeck[i].setSuit("Diamonds");
    }
    //loop to give each card a face value, one card at a time
    for(int i=0;i<NCARDS;i++)
    {   //if i = 0,13,26, or 39, the face value of the card is
        //Ace (four aces total). If i is 1,14,27,40 the face value is two.
        //repeat for all possible values of "i"
        if(i==0||i==13||i==26||i==39)TmpDeck[i].setFace("Ace");
        if(i==1||i==14||i==27||i==40)TmpDeck[i].setFace("Two");
        if(i==2||i==15||i==28||i==41)TmpDeck[i].setFace("Three");
        if(i==3||i==16||i==29||i==42)TmpDeck[i].setFace("Four");
        if(i==4||i==17||i==30||i==43)TmpDeck[i].setFace("Five");
        if(i==5||i==18||i==31||i==44)TmpDeck[i].setFace("Six");
        if(i==6||i==19||i==32||i==45)TmpDeck[i].setFace("Seven");
        if(i==7||i==20||i==33||i==46)TmpDeck[i].setFace("Eight");
        if(i==8||i==21||i==34||i==47)TmpDeck[i].setFace("Nine");
        if(i==9||i==22||i==35||i==48)TmpDeck[i].setFace("Ten");
        if(i==10||i==23||i==36||i==49)TmpDeck[i].setFace("Jack");
        if(i==11||i==24||i==37||i==50)TmpDeck[i].setFace("Queen");
        if(i==12||i==25||i==38||i==51)TmpDeck[i].setFace("King");
    }
    //SHUFFLE DECK OF CARDS
    //create array of integers 0-51
    for(int i=0;i<NCARDS;i++)
        vC[i]=i;
    //perform below shuffle 4 times
    for(int j=0,temp=0;j<4;j++)
    {   //swap each array element with randomly selected element
        for(int i=0;i<NCARDS;i++)
        {
            random=rand()%NCARDS;
            temp=vC[i];
            vC[i]=vC[random];
            vC[random]=temp;
        }
    }
    //move cards from unshuffled deck to shuffled deck, one at a time
    for(int i=0;i<NCARDS;i++)
    {   //use array of shuffled integers as the index for shuffled card array
        Cards[vC[i]].setFace(TmpDeck[i].getFace());
        Cards[vC[i]].setSuit(TmpDeck[i].getSuit());
    }
}
void Deck::getCard(short index)
{
    Cards[index].dspCard();
}
Deck::~Deck(){}

#endif /* DECK_H */

