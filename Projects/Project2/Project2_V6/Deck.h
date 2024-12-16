#ifndef DECK_H
#define DECK_H

#include <iostream>
using namespace std;

#include "Card.h"

class Deck
{
    private:
        Card Cards[52];
        const short NCARDS=52;
        short draws;
        static short NDecks;
    public:
        Deck();
        void getCard(short i){Cards[i].dspCard();}
        short getDrws(){return draws;}//returns draws
        short getNCrd()const{return NCARDS;}//returns NCARDS
        short gNDecks(){return NDecks;}
        Card Draw();
        ~Deck(){NDecks--;}
};

#endif /* DECK_H */

