#include <cstring>
using namespace std;

#include "Card.h"

Card::Card()//default constructor
{
    face=new char[SIZE];
    suit=new char[SIZE];
    strcpy(face," ");
    strcpy(suit," ");
}
Card::Card(char *f,char *s):BCard()//overloaded constructor
{
    face=new char[SIZE];
    suit=new char[SIZE];
    strcpy(face,f);
    strcpy(suit,s);
}
Card::Card(const Card& Old)//copy constructor
{
    face=new char[SIZE];
    suit=new char[SIZE];
    strcpy(face,Old.face);
    strcpy(suit,Old.suit);
}
void Card::operator=(const Card &Old)
{
    strcpy(face,Old.face);
    strcpy(suit,Old.suit);
}
bool Card::operator==(const Card &Old)
{
    if(strcmp(face,Old.face)==0)
        return true;
    else return false;
}
bool Card::operator!=(const Card &Old)
{
    if(strcmp(face,Old.face)!=0)
        return true;
    else return false;
}