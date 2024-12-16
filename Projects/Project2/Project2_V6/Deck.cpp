#include <ctime>
#include <cstring>
using namespace std;

#include "Card.h"
#include "Deck.h"

short Deck::NDecks=0;

Deck::Deck()
{
    NDecks++;
    draws=0;
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
        else if(i==1||i==14||i==27||i==40)TmpDeck[i].setFace("Two");
        else if(i==2||i==15||i==28||i==41)TmpDeck[i].setFace("Three");
        else if(i==3||i==16||i==29||i==42)TmpDeck[i].setFace("Four");
        else if(i==4||i==17||i==30||i==43)TmpDeck[i].setFace("Five");
        else if(i==5||i==18||i==31||i==44)TmpDeck[i].setFace("Six");
        else if(i==6||i==19||i==32||i==45)TmpDeck[i].setFace("Seven");
        else if(i==7||i==20||i==33||i==46)TmpDeck[i].setFace("Eight");
        else if(i==8||i==21||i==34||i==47)TmpDeck[i].setFace("Nine");
        else if(i==9||i==22||i==35||i==48)TmpDeck[i].setFace("Ten");
        else if(i==10||i==23||i==36||i==49)TmpDeck[i].setFace("Jack");
        else if(i==11||i==24||i==37||i==50)TmpDeck[i].setFace("Queen");
        else if(i==12||i==25||i==38||i==51)TmpDeck[i].setFace("King");
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
        Cards[vC[i]]=TmpDeck[i];
        Cards[vC[i]]=TmpDeck[i];
    }
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
            case 0:{C=Cards[0];break;}
            case 1:{C=Cards[1];break;}
            case 2:{C=Cards[2];break;}
            case 3:{C=Cards[3];break;}
            case 4:{C=Cards[4];break;}
            case 5:{C=Cards[5];break;}
            case 6:{C=Cards[6];break;}
            case 7:{C=Cards[7];break;}
            case 8:{C=Cards[8];break;}
            case 9:{C=Cards[9];break;}
            case 10:{C=Cards[10];break;}
            case 11:{C=Cards[11];break;}
            case 12:{C=Cards[12];break;}
            case 13:{C=Cards[13];break;}
            case 14:{C=Cards[14];break;}
            case 15:{C=Cards[15];break;}
            case 16:{C=Cards[16];break;}
            case 17:{C=Cards[17];break;}
            case 18:{C=Cards[18];break;}
            case 19:{C=Cards[19];break;}
            case 20:{C=Cards[20];break;}
            case 21:{C=Cards[21];break;}
            case 22:{C=Cards[22];break;}
            case 23:{C=Cards[23];break;}
            case 24:{C=Cards[24];break;}
            case 25:{C=Cards[25];break;}
            case 26:{C=Cards[26];break;}
            case 27:{C=Cards[27];break;}
            case 28:{C=Cards[28];break;}
            case 29:{C=Cards[29];break;}
            case 30:{C=Cards[30];break;}
            case 31:{C=Cards[31];break;}
            case 32:{C=Cards[32];break;}
            case 33:{C=Cards[33];break;}
            case 34:{C=Cards[34];break;}
            case 35:{C=Cards[35];break;}
            case 36:{C=Cards[36];break;}
            case 37:{C=Cards[37];break;}
            case 38:{C=Cards[38];break;}
            case 39:{C=Cards[39];break;}
            case 40:{C=Cards[40];break;}
            case 41:{C=Cards[41];break;}
            case 42:{C=Cards[42];break;}
            case 43:{C=Cards[43];break;}
            case 44:{C=Cards[44];break;}
            case 45:{C=Cards[45];break;}
            case 46:{C=Cards[46];break;}
            case 47:{C=Cards[47];break;}
            case 48:{C=Cards[48];break;}
            case 49:{C=Cards[49];break;}
            case 50:{C=Cards[50];break;}
            case 51:{C=Cards[51];break;}
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