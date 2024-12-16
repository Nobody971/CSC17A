#include <iostream>
#include <cstring>
using namespace std;

#include "Player.h"
#include "Card.h"

Player::Player()
{
    name=new char[max];
    strcpy(name," ");
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
{   //if hand array is blank at index 0, set index 0 equal to C
    if(strcmp(Hand[0].getFace()," ")==0){Hand[0]=C;}
    //otherwise if hand array is blank at index 1, set index 1 equal to drawn card
    else if(strcmp(Hand[1].getFace()," ")==0){Hand[1]=C;}
    //keep searching for a blank index until one is found
    else if(strcmp(Hand[2].getFace()," ")==0){Hand[2]=C;}
    else if(strcmp(Hand[3].getFace()," ")==0){Hand[3]=C;}
    else if(strcmp(Hand[4].getFace()," ")==0){Hand[4]=C;}
    else if(strcmp(Hand[5].getFace()," ")==0){Hand[5]=C;}
    else if(strcmp(Hand[6].getFace()," ")==0){Hand[6]=C;}
    else if(strcmp(Hand[7].getFace()," ")==0){Hand[7]=C;}
    else if(strcmp(Hand[8].getFace()," ")==0){Hand[8]=C;}
    else if(strcmp(Hand[9].getFace()," ")==0){Hand[9]=C;}
    else if(strcmp(Hand[10].getFace()," ")==0){Hand[10]=C;}
    else if(strcmp(Hand[11].getFace()," ")==0){Hand[11]=C;}
    else if(strcmp(Hand[12].getFace()," ")==0){Hand[12]=C;}
    else if(strcmp(Hand[13].getFace()," ")==0){Hand[13]=C;}
    else if(strcmp(Hand[14].getFace()," ")==0){Hand[14]=C;}
    else if(strcmp(Hand[15].getFace()," ")==0){Hand[15]=C;}
    else if(strcmp(Hand[16].getFace()," ")==0){Hand[16]=C;}
    else if(strcmp(Hand[17].getFace()," ")==0){Hand[17]=C;}
    else if(strcmp(Hand[18].getFace()," ")==0){Hand[18]=C;}
    else if(strcmp(Hand[19].getFace()," ")==0){Hand[19]=C;}
    else if(strcmp(Hand[20].getFace()," ")==0){Hand[20]=C;}
    else if(strcmp(Hand[21].getFace()," ")==0){Hand[21]=C;}
    else if(strcmp(Hand[22].getFace()," ")==0){Hand[22]=C;}
    else if(strcmp(Hand[23].getFace()," ")==0){Hand[23]=C;}
    else if(strcmp(Hand[24].getFace()," ")==0){Hand[24]=C;}
    else if(strcmp(Hand[25].getFace()," ")==0){Hand[25]=C;}
    else if(strcmp(Hand[26].getFace()," ")==0){Hand[26]=C;}
    else if(strcmp(Hand[27].getFace()," ")==0){Hand[27]=C;}
    else if(strcmp(Hand[28].getFace()," ")==0){Hand[28]=C;}
    else if(strcmp(Hand[29].getFace()," ")==0){Hand[29]=C;}
}