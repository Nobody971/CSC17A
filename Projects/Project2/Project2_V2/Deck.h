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
        const short NCARDS=52;
        short draws;
        Deck();
        ~Deck();
    public:
        void getCard(short);//displays card located at specified index
        void getDrws();//returns draws
        Card Draw();
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
void Deck::getDrws(short d)
{
    return draws;
}
Card Deck::Draw()
{
    Card C;//variable to hold contents of drawn card
    //if total number of draws < total number of cards
    if (draws<NCARDS)
    {
        switch(draws)
        {
            //if total number of draws = 14, draw = index 14 of deck array
            case 0:{C.setFace(Cards[0].getFace());C.getSuit(Cards[0].getSuit());break;}
            case 1:{C.setFace(Cards[1].getFace());C.getSuit(Cards[1].getSuit());break;}
            case 2:{C.setFace(Cards[2].getFace());C.getSuit(Cards[2].getSuit());break;}
            case 3:{C.setFace(Cards[3].getFace());C.getSuit(Cards[3].getSuit());break;}
            case 4:{C.setFace(Cards[4].getFace());C.getSuit(Cards[4].getSuit());break;}
            case 5:{C.setFace(Cards[5].getFace());C.getSuit(Cards[5].getSuit());break;}
            case 6:{C.setFace(Cards[6].getFace());C.getSuit(Cards[6].getSuit());break;}
            case 7:{C.setFace(Cards[7].getFace());C.getSuit(Cards[7].getSuit());break;}
            case 8:{C.setFace(Cards[8].getFace());C.getSuit(Cards[8].getSuit());break;}
            case 9:{C.setFace(Cards[9].getFace());C.getSuit(Cards[9].getSuit());break;}
            case 10:{C.setFace(Cards[10].getFace());C.getSuit(Cards[10].getSuit());break;}
            case 11:{C.setFace(Cards[11].getFace());C.getSuit(Cards[11].getSuit());break;}
            case 12:{C.setFace(Cards[12].getFace());C.getSuit(Cards[12].getSuit());break;}
            case 13:{C.setFace(Cards[13].getFace());C.getSuit(Cards[13].getSuit());break;}
            case 14:{C.setFace(Cards[14].getFace());C.getSuit(Cards[14].getSuit());break;}
            //or if total number of draws = 15, draw = index 15 of deck array.
            //case exists for every possible number of total draws (14 through 51)
            case 15:{C.setFace(Cards[15].getFace());C.getSuit(Cards[15].getSuit());break;}
            case 16:{C.setFace(Cards[16].getFace());C.getSuit(Cards[16].getSuit());break;}
            case 17:{C.setFace(Cards[17].getFace());C.getSuit(Cards[17].getSuit());break;}
            case 18:{C.setFace(Cards[18].getFace());C.getSuit(Cards[18].getSuit());break;}
            case 19:{C.setFace(Cards[19].getFace());C.getSuit(Cards[19].getSuit());break;}
            case 20:{C.setFace(Cards[20].getFace());C.getSuit(Cards[20].getSuit());break;}
            case 21:{C.setFace(Cards[21].getFace());C.getSuit(Cards[21].getSuit());break;}
            case 22:{C.setFace(Cards[22].getFace());C.getSuit(Cards[22].getSuit());break;}
            case 23:{C.setFace(Cards[23].getFace());C.getSuit(Cards[23].getSuit());break;}
            case 24:{C.setFace(Cards[24].getFace());C.getSuit(Cards[24].getSuit());break;}
            case 25:{C.setFace(Cards[25].getFace());C.getSuit(Cards[25].getSuit());break;}
            case 26:{C.setFace(Cards[26].getFace());C.getSuit(Cards[26].getSuit());break;}
            case 27:{C.setFace(Cards[27].getFace());C.getSuit(Cards[27].getSuit());break;}
            case 28:{C.setFace(Cards[28].getFace());C.getSuit(Cards[28].getSuit());break;}
            case 29:{C.setFace(Cards[29].getFace());C.getSuit(Cards[29].getSuit());break;}
            case 30:{C.setFace(Cards[30].getFace());C.getSuit(Cards[30].getSuit());break;}
            case 31:{C.setFace(Cards[31].getFace());C.getSuit(Cards[31].getSuit());break;}
            case 32:{C.setFace(Cards[32].getFace());C.getSuit(Cards[32].getSuit());break;}
            case 33:{C.setFace(Cards[33].getFace());C.getSuit(Cards[33].getSuit());break;}
            case 34:{C.setFace(Cards[34].getFace());C.getSuit(Cards[34].getSuit());break;}
            case 35:{C.setFace(Cards[35].getFace());C.getSuit(Cards[35].getSuit());break;}
            case 36:{C.setFace(Cards[36].getFace());C.getSuit(Cards[36].getSuit());break;}
            case 37:{C.setFace(Cards[37].getFace());C.getSuit(Cards[37].getSuit());break;}
            case 38:{C.setFace(Cards[38].getFace());C.getSuit(Cards[38].getSuit());break;}
            case 39:{C.setFace(Cards[39].getFace());C.getSuit(Cards[39].getSuit());break;}
            case 40:{C.setFace(Cards[40].getFace());C.getSuit(Cards[40].getSuit());break;}
            case 41:{C.setFace(Cards[41].getFace());C.getSuit(Cards[41].getSuit());break;}
            case 42:{C.setFace(Cards[42].getFace());C.getSuit(Cards[42].getSuit());break;}
            case 43:{C.setFace(Cards[43].getFace());C.getSuit(Cards[43].getSuit());break;}
            case 44:{C.setFace(Cards[44].getFace());C.getSuit(Cards[44].getSuit());break;}
            case 45:{C.setFace(Cards[45].getFace());C.getSuit(Cards[45].getSuit());break;}
            case 46:{C.setFace(Cards[46].getFace());C.getSuit(Cards[46].getSuit());break;}
            case 47:{C.setFace(Cards[47].getFace());C.getSuit(Cards[47].getSuit());break;}
            case 48:{C.setFace(Cards[48].getFace());C.getSuit(Cards[48].getSuit());break;}
            case 49:{C.setFace(Cards[49].getFace());C.getSuit(Cards[49].getSuit());break;}
            case 50:{C.setFace(Cards[50].getFace());C.getSuit(Cards[50].getSuit());break;}
            case 51:{C.setFace(Cards[51].getFace());C.getSuit(Cards[51].getSuit());break;}
            default: cout<<"Something's gone terribly wrong "
                           "if you're seeing this"<<endl;
        }
        //increment total number of draws by 1
        draws++;
        //return drawn card
        return C;                                                      
    }
    else 
    //otherwise return an error, because this function should not be called
    //if all 52 cards have already been drawn
    {
        cout<<"Error: cannot exceed 52 draws (or 51 starting at 0)"<<endl;
        C.setFace("Invalid");
        C.setSuit("Invalid");
        return C;
    }
}
Deck::~Deck(){}

#endif /* DECK_H */

