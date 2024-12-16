/*File: main.cpp
 * Author: Anastasia Dettman
 * Created Nov 3rd, 2024
 * Purpose:Go Fish*/

//System Libraries
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

//User Libraries
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Profile.h"

//Global Constants - Math/Science/Conversions/Dimensions

//Function Prototypes
//writes formatted float to a file and returns pointer to the float
float *hello(fstream&,float&,Card*);
//returns size of savedata file in bytes
long fndSize(fstream&);
//returns file location of User's profile, otherwise -1
long search(fstream&,Profile&,int,long);
//Initializes player's hands to blank cards
void initHnd(Card[],const int);
//creates and shuffles the deck of cards
void shuffle(Card*,const int);
//Deals cards to each player
void deal(Card[],Card[],int &);
//displays cards in player's hand
void dspHnd(Card[],const int);
//finds matches in beginning hands
void fndMtch(Player&);
//displays number of player's points
void dspPnts(Player&);
//validates player's card request
void vldt(Card[],char[],const int);
//determines if opposing player has the requested card
bool isMtch(Card[],char[]);
//eliminates match from players' hands and increments points
void winMtch(Player&,Player&,char[]);
//tests if player is out of cards
bool isOut (Card[]);
//draws a card from deck
Card goFish(Card[],const int,int&);
//inserts drawn card into hand
void insDraw(Card[],Card&);
//if match is drawn, scores point and removes cards from hand
void mtchDrw(Player&,Card&);
//determines what card p2 will ask for
void p2Rqst(Card[],char[]);
//tests if both players hands are empty
bool isEnd(Card[],Card[]);
//saves User struct to file
void save(fstream&,Profile&,Player&,int,long);
//begin main function
int main() {
    //set the random number seed based on time
    srand(static_cast<unsigned int>(time(0)));
    
    //variable Declarations
    const int NCARDS=52,//number of cards in a deck, not including jokers
              HAND=30,//size of player hand arrays
              MAX=10;//Max size of cstrings for face values and suits
    Card Draw;//Face value and suit of drawn card
    int draws;//number of cards that have been drawn from deck
    char option1,//Y or N for reinputting username
         option2,//Y or N for playing again
         option3,//Y or N for continuing as new user
         option4,//Y or N for creating new profile
         request[MAX];//card being asked for by player  
    bool win=true,//test if player 1 wins the game
         match,//test if opposing player has the requested card
         out,//test if a player ran out of cards
         end;//tests if both players hands are empty
    Deck *Deck1;
    long fSize,//size of savedata file in bytes
         cursor;//current location in savedata file
    Profile User;
    short noPs;//number of players
    Player P[4];//array of 4 players
    
    //CREATE PLAYER PROFILE
        option2='x';
        option4='x';
        User.inputNm();
    do//do while loop so player can play game as many times as desired
    {
        //create deck of cards to be deleted/reset after each game
        Deck1=new Deck;
        //set draws and points equal to zero
        draws=0;
        //call constructor function to reset all player attributes after each game
        for(short i=0;i<noPs;i++)
            P[i].Player();
        //assign each player a number
        for(int i=1;i<=noPs;i++)
            P[i].setNo(i);
        
        //display opening message
        cout<<"GO FISH"<<endl;
        cout<<"Remember to always capitalize the first letter of input and only enter face value, not suit"<<endl;
        cout<<"Have fun!"<<endl<<endl;

        //call deal to deal 7 cards to player 1  
        deal(P1.Hand,Deck,draws);
        //call deal to deal 7 cards to player 2
        deal(P2.Hand,Deck,draws);
        //display message informing player of cards being dealt
        cout<<"Dealing 7 cards to each player..."<<endl;
        //call dspHnd to display player 1's hand
        cout<<"Your cards are"<<endl;
        dspHnd(P1.Hand,HAND);
        cout<<endl;
        cout<<endl;
        //call fndMtch to find matches in player 1's hand, 
        //remove matches from hands, and score points
        fndMtch(P1);
        //call dspPnts to display number of player 1's points
        dspPnts(P1);
        //repeat process for player 2
        fndMtch(P2);
        dspPnts(P2);
        cout<<endl;

        //BEGIN GAME
        //display begin game message
        cout<<"Begin Game!"<<endl<<endl;
        cout<<"You're Player 1, and Player 1 goes first"<<endl;

        do //do while loop for repeating cycle of turns until all cards are gone       
        {
            //call dspHnd to display p1's cards
            cout<<"Your cards are "<<endl;
            dspHnd(P1.Hand,HAND);
            cout<<endl;
            //prompt player to input card request or press x to bypass
            cout<<"Input your card request, or enter x to bypass."<<endl;
            cout<<"Do you have a ";
            //read player's input
            cin.getline(request,MAX);

            //calls vldt to make sure player input properly
            vldt(P1.Hand,request,MAX);

            //display bypass message if player inputs x
            if(strcmp(request,"x")==0)cout<<"You bypassed your turn."<<endl;

            do//do while loop so Player 1 gets another turn if player 2 has requested card
            {
                //call isMtch to return true if player 2 has requested card
                match=isMtch(P2.Hand,request);
                //begin if statement for if isMtch returned true
                if (match)
                {
                    //call winMtch to eliminate match from players' hands and increments points
                    winMtch(P1,P2,request);

                    //call isOut to test if player 1's hand array is all blanks.
                    //returns true if so
                    out=isOut(P1.Hand);

                    //begin if statement for if player is out of cards   
                    if(out)
                    {
                        //display messages informing player
                        cout<<"You just ran out of cards. "
                              "Draw three from the deck"<<endl;

                        //for loop that executes 3 times for 3 cards
                        for(int i=0;i<3;i++)
                        {
                            //if cards are still left in deck array
                            if(draws<NCARDS)
                            {
                                //call goFish to draw card
                                Draw=goFish(Deck,NCARDS,draws);
                                //display card
                                cout<<"Draw "<<(i+1)<<" is the "<<Draw.face<<" of "<<Draw.suit<<endl;
                                //put card in 1st spot of p1's hand array
                                P1.Hand[i].face=Draw.face;
                                P1.Hand[i].suit=Draw.suit;
                            }
                            //if no cards left in deck, say so on display
                            else cout<<"No more cards left in deck"<<endl;
                        }//end for loop

                        //call fndMtch to remove any matches in these cards and score points
                        fndMtch(P1);
                    }//end if statement for player running out of cards

                    //repeat exact process for player 2 running out of cards
                    out=isOut(P2.Hand);
                    if(out)
                    {
                        cout<<"Player 2 just ran out of cards. "
                              "Player 2 draws three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(draws<NCARDS)
                            {
                                Draw=goFish(Deck,NCARDS,draws);
                                P2.Hand[i].face=Draw.face;
                                P2.Hand[i].suit=Draw.suit;
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P2);
                    }

                    
                    //call dspPnts to display player 1's points
                    dspPnts(P1);
                    //call dspPnts again for player 2
                    dspPnts(P2);
                    //display that player 1 gets another turn
                    cout<<endl<<"You get another turn! :D"<<endl;
                    cout<<"Your cards are "<<endl;
                    //call dspHnd to display contents of player 1's hand array
                    dspHnd(P1.Hand,HAND);
                    cout<<endl;
                    //prompt player to input new card request
                    cout<<"Input your card request, or enter x to bypass"<<endl;
                    cout<<"Do you have a ";
                    //read input for card request
                    cin.getline(request,MAX);

                    //call vldt input to make sure player only asks for 
                    //qualifying cards and to eliminate typos
                    vldt(P1.Hand,request,MAX);
                    //if player enters x, display that turn has been bypassed
                    if(request=="x")cout<<"You bypass your turn"<<endl<<endl;

                    //call isMtch to test if opposing player has requested card
                    match=isMtch(P2.Hand,request);
                }//end of if statement for when player isMtch returns true
            }
            //if isMtch returns true and player didn't bypass, then repeat do while loop
            while(match&&strcmp(request,"x")!=0);

            //if statement for when isMtch returns false and the player didn't bypass
            if (!(match)&&strcmp(request,"x")!=0)
            {
                //display 'go fish, draw a card'
                cout<<"Go Fish! Draw a card!"<<endl;

                //if statement that tests if number of cards drawn is less than
                //total number of cards
                if(draws<NCARDS)
                {
                    //if true, then calls goFish and sets drawn card variable equal
                    //to the card that function returns
                    Draw=goFish(Deck,NCARDS,draws);
                    //display drawn card
                    cout<<"You drew the "<<Draw.face<<" of "<<Draw.suit<<endl;

                    //call mtchDrw to determine if player already has drawn card, 
                    //remove matching card from hand and score points.
                    //Otherwise, insert draw into players hand
                    mtchDrw(P1,Draw);

                    //repeat exact process for testing if player 1 ran out of cards
                    //and drawing three cards
                    out=isOut(P1.Hand);
                    if(out)
                    { 
                        cout<<"You just ran out of cards. "
                              "Draw three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(draws<NCARDS)
                            {
                                Draw=goFish(Deck,NCARDS,draws);
                                cout<<"Draw "<<(i+1)<<" is the "<<Draw.face<<" of "<<Draw.suit<<endl;
                                P1.Hand[i].face=Draw.face;
                                P1.Hand[i].suit=Draw.suit;
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P1);
                    }               
                }
                else cout<<"No more cards left in deck"<<endl;

                //call dspPnts again to display both players points
                dspPnts(P1);
                dspPnts(P2);
                cout<<endl;
            }//end of if statement for if isMtch returns false and player didn't bypass

            //PLAYER 2'S TURN
            //announce beginning of player 2's turn on display
            cout<<"Player 2's turn"<<endl;
            cout<<"You're cards are "<<endl;
            //call dspHnd to display contents of p2 hand array
            dspHnd(P1.Hand,HAND);
            cout<<endl;

            //call p2Rqust to determine what card p2 will ask for.
            //function returns bypass if p2 hand array is empty
            p2Rqst(P2.Hand,request);

            //remainder of turn is exactly like p1's turn, but variables//arrays
            //for p2 are passed into functions, and p2Rqst is called in 
            //exchange for reading input from player
            if(strcmp(request,"bypass")!=0)
            {
                cout<<"Do you have a "<<request<<"?"<<endl;

                do
                {
                    match=isMtch(P1.Hand,request);
                    if (match)
                    {
                        winMtch(P2,P1,request);
                        out=isOut(P1.Hand);  
                        if(out)
                        {
                            cout<<"You just ran out of cards. "
                                  "Draw three from the deck"<<endl;
                            for(int i=0;i<3;i++)
                            {
                                if(draws<NCARDS)
                                {
                                    Draw=goFish(Deck,NCARDS,draws);
                                    cout<<"Draw "<<(i+1)<<" is the "<<Draw.face<<" of "<<Draw.suit<<endl;
                                    P1.Hand[i].face=Draw.face;
                                    P1.Hand[i].suit=Draw.suit;
                                }
                                else cout<<"No more cards left in deck"<<endl;
                            }
                            fndMtch(P1);
                        }
                        out=isOut(P2.Hand);  
                        if(out)
                        {
                            cout<<"Player 2 just ran out of cards. "
                                  "Player 2 draws three from the deck"<<endl;
                            for(int i=0;i<3;i++)
                            {
                                if(draws<NCARDS)
                                {
                                    Draw=goFish(Deck,NCARDS,draws);
                                    P2.Hand[i].face=Draw.face;
                                    P2.Hand[i].suit=Draw.suit;
                                }
                                else cout<<"No more cards left in deck"<<endl;
                            }
                            fndMtch(P2);
                        }
                        dspPnts(P1);
                        dspPnts(P2);
                        cout<<endl<<"Player 2 gets another turn"<<endl;
                        cout<<"Your cards are "<<endl;                
                        dspHnd(P1.Hand,HAND);
                        cout<<endl;
                        p2Rqst(P2.Hand,request);

                        if(strcmp(request,"bypass")!=0)
                            cout<<"Do you have a "<<request<<endl;
                        else
                            cout<<"Player two is out of cards and bypasses turn."<<endl<<endl;

                        match=isMtch(P1.Hand,request);
                    }
                }
                while(match);
            }
            else cout<<"Player 2 is out of cards and bypasses turn."<<endl<<endl;

            if ((!match)&&strcmp(request,"bypass")!=0)
            {
                cout<<"Go Fish! Draw a card!"<<endl;
                if(draws<NCARDS)
                {
                    Draw=goFish(Deck,NCARDS,draws);
                    cout<<"Player 2 drew a card."<<endl;
                    mtchDrw(P2,Draw);
                    out=isOut(P2.Hand);
                    if(out)
                    {
                        cout<<"Player 2 just ran out of cards. "
                              "Player 2 draws three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(draws<NCARDS)
                            {
                                Draw=goFish(Deck,NCARDS,draws);
                                P2.Hand[i].face=Draw.face;
                                P2.Hand[i].suit=Draw.suit;
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P2);
                    }
                }
                else cout<<"No more cards left in deck"<<endl;

                dspPnts(P1);
                dspPnts(P2);
                //announce end of p2's turn on display
                cout<<"End of Player 2's turn."<<endl<<endl;
            }
            //call isEnd to test if both player's hands are empty
            end=isEnd(P1.Hand,P2.Hand);
        }
        //end of do while loop. Cycle of turns repeats if isEnd returns false
        while(!(end));

        //Announce end of game
        cout<<"No more cards left in the deck"<<endl;
        cout<<"and no more cards left in either players hands."<<endl;
        cout<<"The game is over."<<endl;
        
        //call dspPnts again to display each player's points
        dspPnts(P1);
        dspPnts(P2);
        cout<<endl;

        //test if p1 has more points
        win=P1.points>P2.points;

        //if true
        if (win)
        {   //announce p1 is winner
            P1.place=FIRST;
            P2.place=SECOND;
            cout<<"YOU ARE THE WINNER!!! YIPPEE! WOOHOO!"<<endl<<endl;
        }//otherwise if p1 points = p2 points
        else if (P1.points==P2.points)
        {   //announce a tie
            P1.place=FIRST;
            P2.place=FIRST;
            cout<<"It's a tie! Nobody wins."
                  " You're all a bunch of losers"<<endl<<endl;           
        }//otherwise
        else
        {   //announce p1 loses
            P1.place=SECOND;
            P2.place=FIRST;
            cout<<"LOOOOOOOOOSER!!! Player 2 wins!"<<endl<<endl;
        }
        
        //SAVE/UPDATE PLAYER PROFILE
        if(option3=='x')
        {
            if(P1.points<=User.hscore)
            {
                cout<<"Your score:      "<<P1.points<<endl;
                cout<<"Your high score: "<<User.hscore<<endl;
            }
            else
            {
                cout<<"New high score!"<<endl;
                save(file,User,P1,sizeof(User),cursor);
            }
        }
        else if(option3!='n'||option3!='N')
        {
            cout<<"Would you like to save your username and score? y for yes and n for no";
            cin.get(option4);
            if(option4=='y'||option4=='Y')save(file,User,P1,sizeof(User),cursor);
        }
        
        //prompt player to input Y to play again or anything else to stop
        cout<<"Would you like to play again? Y for yes and anything else for no"<<endl;
        //read input from player
        cin.get(option2);
        cout<<endl;
        //delete deck of cards
        delete Deck1;
    }//end of do while loop. entire game repeats if player inputs Y
    while(option2=='Y'||option2=='y');

    //clean up files
    file.close();
    extra.close();
    for(int i=0;i<HAND;i++)
    {
        delete []P1.Hand;
        delete []P2.Hand;
    }
    //display end of game
    cout<<"Thanks for playing"<<endl;
    cout<<"END OF GAME";

//exit stage right*/
return 0; }

/*void shuffle(Card *Shffld,const int SIZE)
{
    int random;//for storing randomly generated number
    int vC[SIZE];//to hold shuffled numbers
    Card Deck[SIZE];//unshuffled deck
    
    //CREATE THE DECK OF CARDS
    //assign first 13 cards to spades
    for(int i=0;i<13;i++)
    {
        Deck[i].suit="Spades";
    }
    //assign next 13 cards to clubs
    for(int i=13;i<26;i++)
    {
        Deck[i].suit="Clubs";
    }
    //assign next 13 to hearts
    for(int i=26;i<39;i++)
    {
        Deck[i].suit="Hearts";
    }
    //assign final 13 to diamonds
    for(int i=39;i<52;i++)
    {
        Deck[i].suit="Diamonds";
    }
    //loop to give each card a face value, one card at a time
    for(int card=0;card<SIZE;card++)
    {   //if card = 0,13,26, or 39, the face value of the card is
        //an Ace (four aces total). If card is 1,14,27,40 the face value is two.
        //repeat for all possible values of "card"
        if(card==0||card==13||card==26||card==39)Deck[card].face="Ace";
        if(card==1||card==14||card==27||card==40)Deck[card].face="Two";
        if(card==2||card==15||card==28||card==41)Deck[card].face="Three";
        if(card==3||card==16||card==29||card==42)Deck[card].face="Four";
        if(card==4||card==17||card==30||card==43)Deck[card].face="Five";
        if(card==5||card==18||card==31||card==44)Deck[card].face="Six";
        if(card==6||card==19||card==32||card==45)Deck[card].face="Seven";
        if(card==7||card==20||card==33||card==46)Deck[card].face="Eight";
        if(card==8||card==21||card==34||card==47)Deck[card].face="Nine";
        if(card==9||card==22||card==35||card==48)Deck[card].face="Ten";
        if(card==10||card==23||card==36||card==49)Deck[card].face="Jack";
        if(card==11||card==24||card==37||card==50)Deck[card].face="Queen";
        if(card==12||card==25||card==38||card==51)Deck[card].face="King";
    }
    //SHUFFLE DECK OF CARDS
    //create array of integers 0-51
    for(int i=0;i<SIZE;i++)
        vC[i]=i;
    //perform below shuffle 4 times
    for(int j=0,temp=0;j<4;j++)
    {   //swap each array element with randomly selected element
        for(int i=0;i<SIZE;i++)
        {
            random=rand()%SIZE;
            temp=vC[i];
            vC[i]=vC[random];
            vC[random]=temp;
        }
    }
    //move cards from unshuffled deck to shuffled deck, one at a time
    for(int i=0;i<SIZE;i++)
    {   //use array of shuffled integers as the index for shuffled card array
        Shffld[vC[i]].face=Deck[i].face;
        Shffld[vC[i]].suit=Deck[i].suit;
    }
}
void deal(Card Hand[],Card Deck[],int &draws)
{   //i=0, loop while i<7, increment i and # of draws after each execution
    for(int i=0;i<7;i++,draws++)
    {   //(contents of hand array at index #i) = (contents of card array at 
        //index #(# of draws))
        Hand[i].face=Deck[draws].face;
        Hand[i].suit=Deck[draws].suit;
    }
}
void dspHnd(Card Hand[],const int HAND)
{   
    //i=0, loop while i<(max # of cards held), increment i after each execution
    for(int i=0;i<HAND;i++)
        if(strcmp(Hand[i].face," ")!=0)
        {
            {   //display contents of hand array at index #i
                cout<<Hand[i].face<<" of "<<Hand[i].suit<<endl;
            }
        }
}
void fndMtch(Player &P)
{   //if hand array contents at index 0 = contents at index 1, 
    //(and index 0 isn't blank) set both indexes to blank and increment points 
    //by 1. announce what cards matched
    if(strcmp(P.Hand[0].face,P.Hand[1].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<((strcmp(P.Hand[0].face,"Six"))==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.points++;
    }
    //otherwise if index 0 = index 2 then do the same to these indexes instead
    else if(strcmp(P.Hand[0].face,P.Hand[2].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<(strcmp(P.Hand[0].face,"Six")==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.points++;
    }
    //otherwise if index 0 = index 3 etc. etc. etc.
    else if(strcmp(P.Hand[0].face,P.Hand[3].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<(strcmp(P.Hand[0].face,"Six")==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[0].face,P.Hand[4].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<(strcmp(P.Hand[0].face,"Six")==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[0].face,P.Hand[5].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<(strcmp(P.Hand[0].face,"Six")==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[0].face,P.Hand[6].face)==0&&(strcmp(P.Hand[0].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[0].face<<(strcmp(P.Hand[0].face,"Six")==0?"es! ":"s! ");
        P.Hand[0].face=" ";
        P.Hand[0].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }
    //if index 1 = index 2 then do the same. Repeat this process until all cards
    //from indexes 0-7 have been tested for matches
    if(strcmp(P.Hand[1].face,P.Hand[2].face)==0&&(strcmp(P.Hand[1].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[1].face<<((strcmp(P.Hand[1].face,"Six"))==0?"es! ":"s! ");
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[1].face,P.Hand[3].face)==0&&(strcmp(P.Hand[1].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[1].face<<((strcmp(P.Hand[1].face,"Six"))==0?"es! ":"s! ");
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[1].face,P.Hand[4].face)==0&&(strcmp(P.Hand[1].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[1].face<<((strcmp(P.Hand[1].face,"Six"))==0?"es! ":"s! ");
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[1].face,P.Hand[5].face)==0&&(strcmp(P.Hand[1].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[1].face<<((strcmp(P.Hand[1].face,"Six"))==0?"es! ":"s! ");
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[1].face,P.Hand[6].face)==0&&(strcmp(P.Hand[1].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[1].face<<((strcmp(P.Hand[1].face,"Six"))==0?"es! ":"s! ");
        P.Hand[1].face=" ";
        P.Hand[1].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }

    if(strcmp(P.Hand[2].face,P.Hand[3].face)==0&&(strcmp(P.Hand[2].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[2].face<<((strcmp(P.Hand[2].face,"Six"))==0?"es! ":"s! ");
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[2].face,P.Hand[4].face)==0&&(strcmp(P.Hand[2].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[2].face<<((strcmp(P.Hand[2].face,"Six"))==0?"es! ":"s! ");
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[2].face,P.Hand[5].face)==0&&(strcmp(P.Hand[2].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[2].face<<((strcmp(P.Hand[2].face,"Six"))==0?"es! ":"s! ");
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[2].face,P.Hand[6].face)==0&&(strcmp(P.Hand[2].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[2].face<<((strcmp(P.Hand[2].face,"Six"))==0?"es! ":"s! ");
        P.Hand[2].face=" ";
        P.Hand[2].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }

    if(strcmp(P.Hand[3].face,P.Hand[4].face)==0&&(strcmp(P.Hand[3].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[3].face<<((strcmp(P.Hand[3].face,"Six"))==0?"es! ":"s! ");
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[3].face,P.Hand[5].face)==0&&(strcmp(P.Hand[3].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[3].face<<((strcmp(P.Hand[3].face,"Six"))==0?"es! ":"s! ");
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[3].face,P.Hand[6].face)==0&&(strcmp(P.Hand[3].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[3].face<<((strcmp(P.Hand[3].face,"Six"))==0?"es! ":"s! ");
        P.Hand[3].face=" ";
        P.Hand[3].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }

    if(strcmp(P.Hand[4].face,P.Hand[5].face)==0&&(strcmp(P.Hand[4].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[4].face<<((strcmp(P.Hand[4].face,"Six"))==0?"es! ":"s! ");
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.points++;
    }
    else if(strcmp(P.Hand[4].face,P.Hand[6].face)==0&&(strcmp(P.Hand[4].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[4].face<<((strcmp(P.Hand[4].face,"Six"))==0?"es! ":"s! ");
        P.Hand[4].face=" ";
        P.Hand[4].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }

    if(strcmp(P.Hand[5].face,P.Hand[6].face)==0&&(strcmp(P.Hand[5].face," ")!=0))
    {
        cout<<"Player "<<P.number<<" has two "<<P.Hand[5].face<<((strcmp(P.Hand[5].face,"Six"))==0?"es! ":"s! ");
        P.Hand[5].face=" ";
        P.Hand[5].suit=" ";
        P.Hand[6].face=" ";
        P.Hand[6].suit=" ";
        P.points++;
    }
}
void dspPnts(Player &P)
{
    //display number of points player has won
    cout<<"Player "<<P.number<<" has "<<P.points<<(P.points==1?" point":" points")<<endl;
}
void vldt(Card Hand[],char request[],const int MAX)
{
    //while input doesn't match anything in the player hand array AND input 
    //isn't x (x means bypass)
    while(!(strcmp(request,Hand[0].face)==0||strcmp(request,Hand[1].face)==0||
            strcmp(request,Hand[2].face)==0||strcmp(request,Hand[3].face)==0||
            strcmp(request,Hand[4].face)==0||strcmp(request,Hand[5].face)==0||
            strcmp(request,Hand[6].face)==0||strcmp(request,Hand[7].face)==0||
            strcmp(request,Hand[8].face)==0||strcmp(request,Hand[9].face)==0||
            strcmp(request,Hand[10].face)==0||strcmp(request,Hand[11].face)==0||
            strcmp(request,Hand[12].face)==0||strcmp(request,Hand[13].face)==0||
            strcmp(request,Hand[14].face)==0||strcmp(request,Hand[15].face)==0||
            strcmp(request,Hand[16].face)==0||strcmp(request,Hand[17].face)==0||
            strcmp(request,Hand[18].face)==0||strcmp(request,Hand[19].face)==0||
            strcmp(request,Hand[20].face)==0||strcmp(request,Hand[21].face)==0||
            strcmp(request,Hand[22].face)==0||strcmp(request,Hand[23].face)==0||
            strcmp(request,Hand[24].face)==0||strcmp(request,Hand[25].face)==0||
            strcmp(request,Hand[26].face)==0||strcmp(request,Hand[27].face)==0||
            strcmp(request,Hand[28].face)==0||strcmp(request,Hand[29].face)==0||
            strcmp(request,"x")==0))
    {
        //prompt player to try again
        cout<<"Incorrect format or you don't have that card."<<endl;
        cout<<"Try again. Make sure the first letter is uppercase."<<endl;
        cout<<"If you are out of cards, input x to bypass turn."<<endl;
        cout<<"Do you have a ";
        //read new input
        cin.getline(request,MAX);
    }
    //while input is x AND contents of player hand array aren't blank
    while(strcmp(request,"x")==0&&!(
          strcmp(Hand[0].face," ")==0&&strcmp(Hand[1].face," ")==0&&
          strcmp(Hand[2].face," ")==0&&strcmp(Hand[3].face," ")==0&&
          strcmp(Hand[4].face," ")==0&&strcmp(Hand[5].face," ")==0&&
          strcmp(Hand[6].face," ")==0&&strcmp(Hand[7].face," ")==0&&
          strcmp(Hand[8].face," ")==0&&strcmp(Hand[9].face," ")==0&&
          strcmp(Hand[10].face," ")==0&&strcmp(Hand[11].face," ")==0&&
          strcmp(Hand[12].face," ")==0&&strcmp(Hand[13].face," ")==0&&
          strcmp(Hand[14].face," ")==0&&strcmp(Hand[15].face," ")==0&&
          strcmp(Hand[16].face," ")==0&&strcmp(Hand[17].face," ")==0&&
          strcmp(Hand[18].face," ")==0&&strcmp(Hand[19].face," ")==0&&
          strcmp(Hand[20].face," ")==0&&strcmp(Hand[21].face," ")==0&&
          strcmp(Hand[22].face," ")==0&&strcmp(Hand[23].face," ")==0&&
          strcmp(Hand[24].face," ")==0&&strcmp(Hand[25].face," ")==0&&
          strcmp(Hand[26].face," ")==0&&strcmp(Hand[27].face," ")==0&&
          strcmp(Hand[28].face," ")==0&&strcmp(Hand[29].face," ")==0))
    {
        //prompt for new input
        cout<<"You can't bypass your turn if you still have "
              "cards. Try again."<<endl;
        cout<<"Input card request and press enter"<<endl;
        cout<<"Do you have a ";
        //read new input
        cin.getline(request,MAX);
        if(strcmp(request,"x")!=0)vldt(Hand,request,MAX);
    }
}
bool isMtch(Card Hand[],char request[])
{   //if player request = (any of the indexes in opposing players hand array)
    if (strcmp(request,Hand[0].face)==0||strcmp(request,Hand[1].face)==0||
        strcmp(request,Hand[2].face)==0||strcmp(request,Hand[3].face)==0||
        strcmp(request,Hand[4].face)==0||strcmp(request,Hand[5].face)==0||
        strcmp(request,Hand[6].face)==0||strcmp(request,Hand[7].face)==0||
        strcmp(request,Hand[8].face)==0||strcmp(request,Hand[9].face)==0||
        strcmp(request,Hand[10].face)==0||strcmp(request,Hand[11].face)==0||
        strcmp(request,Hand[12].face)==0||strcmp(request,Hand[13].face)==0||
        strcmp(request,Hand[14].face)==0||strcmp(request,Hand[15].face)==0||
        strcmp(request,Hand[16].face)==0||strcmp(request,Hand[17].face)==0||
        strcmp(request,Hand[18].face)==0||strcmp(request,Hand[19].face)==0||
        strcmp(request,Hand[20].face)==0||strcmp(request,Hand[21].face)==0||
        strcmp(request,Hand[22].face)==0||strcmp(request,Hand[23].face)==0||
        strcmp(request,Hand[24].face)==0||strcmp(request,Hand[25].face)==0||
        strcmp(request,Hand[26].face)==0||strcmp(request,Hand[27].face)==0||
        strcmp(request,Hand[28].face)==0||strcmp(request,Hand[29].face)==0)
    {
        //return true
        return true;
    }
    //otherwise return false
    else return false;
}
void winMtch(Player &Asker,Player &Asked,char request[])
{
    //announce that won point and that match was found
    cout<<"Player "<<Asker.number<<" wins a match and scores a point! The matching cards are "
                  "removed from both hands"<<endl;
    //increment player points by one
    Asker.points++;

    //for first player, if (hand array index 0) = requested card, hand array 
    //index 0 = blank
    if(strcmp(Asker.Hand[0].face,request)==0){Asker.Hand[0].face=" ";Asker.Hand[0].suit=" ";}
    //otherwise if (hand array index 1) = requested card, hand array index 0 = blank.
    //keep repeated for every index of hand array
    else if(strcmp(Asker.Hand[0].face,request)==0){Asker.Hand[0].face=" ";Asker.Hand[0].suit=" ";}
    else if(strcmp(Asker.Hand[1].face,request)==0){Asker.Hand[1].face=" ";Asker.Hand[1].suit=" ";}
    else if(strcmp(Asker.Hand[2].face,request)==0){Asker.Hand[2].face=" ";Asker.Hand[2].suit=" ";}
    else if(strcmp(Asker.Hand[3].face,request)==0){Asker.Hand[3].face=" ";Asker.Hand[3].suit=" ";}
    else if(strcmp(Asker.Hand[4].face,request)==0){Asker.Hand[4].face=" ";Asker.Hand[4].suit=" ";}
    else if(strcmp(Asker.Hand[5].face,request)==0){Asker.Hand[5].face=" ";Asker.Hand[5].suit=" ";}
    else if(strcmp(Asker.Hand[6].face,request)==0){Asker.Hand[6].face=" ";Asker.Hand[6].suit=" ";}
    else if(strcmp(Asker.Hand[7].face,request)==0){Asker.Hand[7].face=" ";Asker.Hand[7].suit=" ";}
    else if(strcmp(Asker.Hand[8].face,request)==0){Asker.Hand[8].face=" ";Asker.Hand[8].suit=" ";}
    else if(strcmp(Asker.Hand[9].face,request)==0){Asker.Hand[9].face=" ";Asker.Hand[9].suit=" ";}
    else if(strcmp(Asker.Hand[10].face,request)==0){Asker.Hand[10].face=" ";Asker.Hand[10].suit=" ";}
    else if(strcmp(Asker.Hand[11].face,request)==0){Asker.Hand[11].face=" ";Asker.Hand[11].suit=" ";}
    else if(strcmp(Asker.Hand[12].face,request)==0){Asker.Hand[12].face=" ";Asker.Hand[12].suit=" ";}
    else if(strcmp(Asker.Hand[13].face,request)==0){Asker.Hand[13].face=" ";Asker.Hand[13].suit=" ";}
    else if(strcmp(Asker.Hand[14].face,request)==0){Asker.Hand[14].face=" ";Asker.Hand[14].suit=" ";}
    else if(strcmp(Asker.Hand[15].face,request)==0){Asker.Hand[15].face=" ";Asker.Hand[15].suit=" ";}
    else if(strcmp(Asker.Hand[16].face,request)==0){Asker.Hand[16].face=" ";Asker.Hand[16].suit=" ";}
    else if(strcmp(Asker.Hand[17].face,request)==0){Asker.Hand[17].face=" ";Asker.Hand[17].suit=" ";}
    else if(strcmp(Asker.Hand[18].face,request)==0){Asker.Hand[18].face=" ";Asker.Hand[18].suit=" ";}
    else if(strcmp(Asker.Hand[19].face,request)==0){Asker.Hand[19].face=" ";Asker.Hand[19].suit=" ";}
    else if(strcmp(Asker.Hand[20].face,request)==0){Asker.Hand[20].face=" ";Asker.Hand[20].suit=" ";}
    else if(strcmp(Asker.Hand[21].face,request)==0){Asker.Hand[21].face=" ";Asker.Hand[21].suit=" ";}
    else if(strcmp(Asker.Hand[22].face,request)==0){Asker.Hand[22].face=" ";Asker.Hand[22].suit=" ";}
    else if(strcmp(Asker.Hand[23].face,request)==0){Asker.Hand[23].face=" ";Asker.Hand[23].suit=" ";}
    else if(strcmp(Asker.Hand[24].face,request)==0){Asker.Hand[24].face=" ";Asker.Hand[24].suit=" ";}
    else if(strcmp(Asker.Hand[25].face,request)==0){Asker.Hand[25].face=" ";Asker.Hand[25].suit=" ";}
    else if(strcmp(Asker.Hand[26].face,request)==0){Asker.Hand[26].face=" ";Asker.Hand[26].suit=" ";}
    else if(strcmp(Asker.Hand[27].face,request)==0){Asker.Hand[27].face=" ";Asker.Hand[27].suit=" ";}
    else if(strcmp(Asker.Hand[28].face,request)==0){Asker.Hand[28].face=" ";Asker.Hand[28].suit=" ";}
    else if(strcmp(Asker.Hand[29].face,request)==0){Asker.Hand[29].face=" ";Asker.Hand[29].suit=" ";}

    //repeat process for second player
    if(strcmp(Asked.Hand[0].face,request)==0){Asked.Hand[0].face=" ";Asked.Hand[0].suit=" ";}
    else if(strcmp(Asked.Hand[0].face,request)==0){Asked.Hand[0].face=" ";Asked.Hand[0].suit=" ";}
    else if(strcmp(Asked.Hand[1].face,request)==0){Asked.Hand[1].face=" ";Asked.Hand[1].suit=" ";}
    else if(strcmp(Asked.Hand[2].face,request)==0){Asked.Hand[2].face=" ";Asked.Hand[2].suit=" ";}
    else if(strcmp(Asked.Hand[3].face,request)==0){Asked.Hand[3].face=" ";Asked.Hand[3].suit=" ";}
    else if(strcmp(Asked.Hand[4].face,request)==0){Asked.Hand[4].face=" ";Asked.Hand[4].suit=" ";}
    else if(strcmp(Asked.Hand[5].face,request)==0){Asked.Hand[5].face=" ";Asked.Hand[5].suit=" ";}
    else if(strcmp(Asked.Hand[6].face,request)==0){Asked.Hand[6].face=" ";Asked.Hand[6].suit=" ";}
    else if(strcmp(Asked.Hand[7].face,request)==0){Asked.Hand[7].face=" ";Asked.Hand[7].suit=" ";}
    else if(strcmp(Asked.Hand[8].face,request)==0){Asked.Hand[8].face=" ";Asked.Hand[8].suit=" ";}
    else if(strcmp(Asked.Hand[9].face,request)==0){Asked.Hand[9].face=" ";Asked.Hand[9].suit=" ";}
    else if(strcmp(Asked.Hand[10].face,request)==0){Asked.Hand[10].face=" ";Asked.Hand[10].suit=" ";}
    else if(strcmp(Asked.Hand[11].face,request)==0){Asked.Hand[11].face=" ";Asked.Hand[11].suit=" ";}
    else if(strcmp(Asked.Hand[12].face,request)==0){Asked.Hand[12].face=" ";Asked.Hand[12].suit=" ";}
    else if(strcmp(Asked.Hand[13].face,request)==0){Asked.Hand[13].face=" ";Asked.Hand[13].suit=" ";}
    else if(strcmp(Asked.Hand[14].face,request)==0){Asked.Hand[14].face=" ";Asked.Hand[14].suit=" ";}
    else if(strcmp(Asked.Hand[15].face,request)==0){Asked.Hand[15].face=" ";Asked.Hand[15].suit=" ";}
    else if(strcmp(Asked.Hand[16].face,request)==0){Asked.Hand[16].face=" ";Asked.Hand[16].suit=" ";}
    else if(strcmp(Asked.Hand[17].face,request)==0){Asked.Hand[17].face=" ";Asked.Hand[17].suit=" ";}
    else if(strcmp(Asked.Hand[18].face,request)==0){Asked.Hand[18].face=" ";Asked.Hand[18].suit=" ";}
    else if(strcmp(Asked.Hand[19].face,request)==0){Asked.Hand[19].face=" ";Asked.Hand[19].suit=" ";}
    else if(strcmp(Asked.Hand[20].face,request)==0){Asked.Hand[20].face=" ";Asked.Hand[20].suit=" ";}
    else if(strcmp(Asked.Hand[21].face,request)==0){Asked.Hand[21].face=" ";Asked.Hand[21].suit=" ";}
    else if(strcmp(Asked.Hand[22].face,request)==0){Asked.Hand[22].face=" ";Asked.Hand[22].suit=" ";}
    else if(strcmp(Asked.Hand[23].face,request)==0){Asked.Hand[23].face=" ";Asked.Hand[23].suit=" ";}
    else if(strcmp(Asked.Hand[24].face,request)==0){Asked.Hand[24].face=" ";Asked.Hand[24].suit=" ";}
    else if(strcmp(Asked.Hand[25].face,request)==0){Asked.Hand[25].face=" ";Asked.Hand[25].suit=" ";}
    else if(strcmp(Asked.Hand[26].face,request)==0){Asked.Hand[26].face=" ";Asked.Hand[26].suit=" ";}
    else if(strcmp(Asked.Hand[27].face,request)==0){Asked.Hand[27].face=" ";Asked.Hand[27].suit=" ";}
    else if(strcmp(Asked.Hand[28].face,request)==0){Asked.Hand[28].face=" ";Asked.Hand[28].suit=" ";}
    else if(strcmp(Asked.Hand[29].face,request)==0){Asked.Hand[29].face=" ";Asked.Hand[29].suit=" ";}
}
bool isOut (Card Hand[])
{
    //if every index of hand array = blank
    if(strcmp(Hand[0].face," ")==0&&strcmp(Hand[1].face," ")==0&&
       strcmp(Hand[2].face," ")==0&&strcmp(Hand[3].face," ")==0&&
       strcmp(Hand[4].face," ")==0&&strcmp(Hand[5].face," ")==0&&
       strcmp(Hand[6].face," ")==0&&strcmp(Hand[7].face," ")==0&&
       strcmp(Hand[8].face," ")==0&&strcmp(Hand[9].face," ")==0&&
       strcmp(Hand[10].face," ")==0&&strcmp(Hand[11].face," ")==0&&
       strcmp(Hand[12].face," ")==0&&strcmp(Hand[13].face," ")==0&&
       strcmp(Hand[14].face," ")==0&&strcmp(Hand[15].face," ")==0&&
       strcmp(Hand[16].face," ")==0&&strcmp(Hand[17].face," ")==0&&
       strcmp(Hand[18].face," ")==0&&strcmp(Hand[19].face," ")==0&&
       strcmp(Hand[20].face," ")==0&&strcmp(Hand[21].face," ")==0&&
       strcmp(Hand[22].face," ")==0&&strcmp(Hand[23].face," ")==0&&
       strcmp(Hand[24].face," ")==0&&strcmp(Hand[25].face," ")==0&&
       strcmp(Hand[26].face," ")==0&&strcmp(Hand[27].face," ")==0&&
       strcmp(Hand[28].face," ")==0&&strcmp(Hand[29].face," ")==0)
    {
        //return true
        return true;
    }
    //otherwise return false
    else return false;
}
Card goFish(Card Deck[],const int NCARDS,int &draws)
{
    Card Draw;//variable to hold contents of drawn card
    //if total number of draws < total number of cards
    if (draws<NCARDS)
    {
        switch(draws)
        {
            //if total number of draws = 14, draw = index 14 of deck array
            case 14:{Draw.face=Deck[14].face;Draw.suit=Deck[14].suit;break;}
            //or if total number of draws = 15, draw = index 15 of deck array.
            //case exists for every possible number of total draws (14 through 51)
            case 15:{Draw.face=Deck[15].face;Draw.suit=Deck[15].suit;break;}
            case 16:{Draw.face=Deck[16].face;Draw.suit=Deck[16].suit;break;}
            case 17:{Draw.face=Deck[17].face;Draw.suit=Deck[17].suit;break;}
            case 18:{Draw.face=Deck[18].face;Draw.suit=Deck[18].suit;break;}
            case 19:{Draw.face=Deck[19].face;Draw.suit=Deck[19].suit;break;}
            case 20:{Draw.face=Deck[20].face;Draw.suit=Deck[20].suit;break;}
            case 21:{Draw.face=Deck[21].face;Draw.suit=Deck[21].suit;break;}
            case 22:{Draw.face=Deck[22].face;Draw.suit=Deck[22].suit;break;}
            case 23:{Draw.face=Deck[23].face;Draw.suit=Deck[23].suit;break;}
            case 24:{Draw.face=Deck[24].face;Draw.suit=Deck[24].suit;break;}
            case 25:{Draw.face=Deck[25].face;Draw.suit=Deck[25].suit;break;}
            case 26:{Draw.face=Deck[26].face;Draw.suit=Deck[26].suit;break;}
            case 27:{Draw.face=Deck[27].face;Draw.suit=Deck[27].suit;break;}
            case 28:{Draw.face=Deck[28].face;Draw.suit=Deck[28].suit;break;}
            case 29:{Draw.face=Deck[29].face;Draw.suit=Deck[29].suit;break;}
            case 30:{Draw.face=Deck[30].face;Draw.suit=Deck[30].suit;break;}
            case 31:{Draw.face=Deck[31].face;Draw.suit=Deck[31].suit;break;}
            case 32:{Draw.face=Deck[32].face;Draw.suit=Deck[32].suit;break;}
            case 33:{Draw.face=Deck[33].face;Draw.suit=Deck[33].suit;break;}
            case 34:{Draw.face=Deck[34].face;Draw.suit=Deck[34].suit;break;}
            case 35:{Draw.face=Deck[35].face;Draw.suit=Deck[35].suit;break;}
            case 36:{Draw.face=Deck[36].face;Draw.suit=Deck[36].suit;break;}
            case 37:{Draw.face=Deck[37].face;Draw.suit=Deck[37].suit;break;}
            case 38:{Draw.face=Deck[38].face;Draw.suit=Deck[38].suit;break;}
            case 39:{Draw.face=Deck[39].face;Draw.suit=Deck[39].suit;break;}
            case 40:{Draw.face=Deck[40].face;Draw.suit=Deck[40].suit;break;}
            case 41:{Draw.face=Deck[41].face;Draw.suit=Deck[41].suit;break;}
            case 42:{Draw.face=Deck[42].face;Draw.suit=Deck[42].suit;break;}
            case 43:{Draw.face=Deck[43].face;Draw.suit=Deck[43].suit;break;}
            case 44:{Draw.face=Deck[44].face;Draw.suit=Deck[44].suit;break;}
            case 45:{Draw.face=Deck[45].face;Draw.suit=Deck[45].suit;break;}
            case 46:{Draw.face=Deck[46].face;Draw.suit=Deck[46].suit;break;}
            case 47:{Draw.face=Deck[47].face;Draw.suit=Deck[47].suit;break;}
            case 48:{Draw.face=Deck[48].face;Draw.suit=Deck[48].suit;break;}
            case 49:{Draw.face=Deck[49].face;Draw.suit=Deck[49].suit;break;}
            case 50:{Draw.face=Deck[50].face;Draw.suit=Deck[50].suit;break;}
            case 51:{Draw.face=Deck[51].face;Draw.suit=Deck[51].suit;break;}
            default: cout<<"Something's gone terribly wrong "
                           "if you're seeing this"<<endl;
        }
        //increment total number of draws by 1
        draws++;
        //return drawn card
        return Draw;                                                      
    }
    else 
    //otherwise return an error, because this function should not be called
    //if all 52 cards have already been drawn
    {
        cout<<"Error in goFish function"<<endl;
        Draw.face="Invalid";
        Draw.suit="Invalid";
        return Draw;
    }
}
void insDraw(Card Hand[],Card &Draw)
{
    //if hand array is blank at index 0, set index 0 equal to drawn card
    if (Hand[0].face==" "){Hand[0].face=Draw.face;Hand[0].suit=Draw.suit;}
    //otherwise if hand array is blank at index 1, set index 1 equal to drawn card
    else if (Hand[1].face==" "){Hand[1].face=Draw.face;Hand[1].suit=Draw.suit;}
    //keep searching for a blank index until one is found
    else if (Hand[2].face==" "){Hand[2].face=Draw.face;Hand[2].suit=Draw.suit;}
    else if (Hand[3].face==" "){Hand[3].face=Draw.face;Hand[3].suit=Draw.suit;}
    else if (Hand[4].face==" "){Hand[4].face=Draw.face;Hand[4].suit=Draw.suit;}
    else if (Hand[5].face==" "){Hand[5].face=Draw.face;Hand[5].suit=Draw.suit;}
    else if (Hand[6].face==" "){Hand[6].face=Draw.face;Hand[6].suit=Draw.suit;}
    else if (Hand[7].face==" "){Hand[7].face=Draw.face;Hand[7].suit=Draw.suit;}
    else if (Hand[8].face==" "){Hand[8].face=Draw.face;Hand[8].suit=Draw.suit;}
    else if (Hand[9].face==" "){Hand[9].face=Draw.face;Hand[9].suit=Draw.suit;}
    else if (Hand[10].face==" "){Hand[10].face=Draw.face;Hand[10].suit=Draw.suit;}
    else if (Hand[11].face==" "){Hand[11].face=Draw.face;Hand[11].suit=Draw.suit;}
    else if (Hand[12].face==" "){Hand[12].face=Draw.face;Hand[12].suit=Draw.suit;}
    else if (Hand[13].face==" "){Hand[13].face=Draw.face;Hand[13].suit=Draw.suit;}
    else if (Hand[14].face==" "){Hand[14].face=Draw.face;Hand[14].suit=Draw.suit;}
    else if (Hand[15].face==" "){Hand[15].face=Draw.face;Hand[15].suit=Draw.suit;}
    else if (Hand[16].face==" "){Hand[16].face=Draw.face;Hand[16].suit=Draw.suit;}
    else if (Hand[17].face==" "){Hand[17].face=Draw.face;Hand[17].suit=Draw.suit;}
    else if (Hand[18].face==" "){Hand[18].face=Draw.face;Hand[18].suit=Draw.suit;}
    else if (Hand[19].face==" "){Hand[19].face=Draw.face;Hand[19].suit=Draw.suit;}
    else if (Hand[20].face==" "){Hand[20].face=Draw.face;Hand[20].suit=Draw.suit;}
    else if (Hand[21].face==" "){Hand[21].face=Draw.face;Hand[21].suit=Draw.suit;}
    else if (Hand[22].face==" "){Hand[22].face=Draw.face;Hand[22].suit=Draw.suit;}
    else if (Hand[23].face==" "){Hand[23].face=Draw.face;Hand[23].suit=Draw.suit;}
    else if (Hand[24].face==" "){Hand[24].face=Draw.face;Hand[24].suit=Draw.suit;}
    else if (Hand[25].face==" "){Hand[25].face=Draw.face;Hand[25].suit=Draw.suit;}
    else if (Hand[26].face==" "){Hand[26].face=Draw.face;Hand[26].suit=Draw.suit;}
    else if (Hand[27].face==" "){Hand[27].face=Draw.face;Hand[27].suit=Draw.suit;}
    else if (Hand[28].face==" "){Hand[28].face=Draw.face;Hand[28].suit=Draw.suit;}
    else if (Hand[29].face==" "){Hand[29].face=Draw.face;Hand[29].suit=Draw.suit;}
}
void mtchDrw(Player &P,Card &Draw)
{
    //if drawn card = (any of the indexes in hand array)
    if(Draw.face==P.Hand[0].face||Draw.face==P.Hand[1].face||
       Draw.face==P.Hand[2].face||Draw.face==P.Hand[3].face||
       Draw.face==P.Hand[4].face||Draw.face==P.Hand[5].face||
       Draw.face==P.Hand[6].face||Draw.face==P.Hand[7].face||
       Draw.face==P.Hand[8].face||Draw.face==P.Hand[9].face||
       Draw.face==P.Hand[10].face||Draw.face==P.Hand[11].face||
       Draw.face==P.Hand[12].face||Draw.face==P.Hand[13].face||
       Draw.face==P.Hand[14].face||Draw.face==P.Hand[15].face||
       Draw.face==P.Hand[16].face||Draw.face==P.Hand[17].face||
       Draw.face==P.Hand[18].face||Draw.face==P.Hand[19].face||
       Draw.face==P.Hand[20].face||Draw.face==P.Hand[21].face||
       Draw.face==P.Hand[22].face||Draw.face==P.Hand[23].face||
       Draw.face==P.Hand[24].face||Draw.face==P.Hand[25].face||
       Draw.face==P.Hand[26].face||Draw.face==P.Hand[27].face||
       Draw.face==P.Hand[28].face||Draw.face==P.Hand[29].face)
    {
        //announce the found match and won point
        cout<<"Player "<<P.number<<" has two "<<Draw.face<<(strcmp(Draw.face,"Six")==0?"es! ":"s! ");
        cout<<"Player "<<P.number<<" wins a point!"<<endl;
        //if drawn card = (index 0 of hand array), then index 0 = blank.
        //increment points by 1
        if(Draw.face==P.Hand[0].face){P.Hand[0].face=" ";P.Hand[0].suit=" ";P.points++;}
        //otherwise if drawn card = (index 1 of hand array), then index 1 = blank.
        //increment points by 1
        else if(Draw.face==P.Hand[1].face){P.Hand[1].face=" ";P.Hand[1].suit=" ";P.points++;}
        //keep testing until the index with matching card is found
        else if(Draw.face==P.Hand[2].face){P.Hand[2].face=" ";P.Hand[2].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[3].face){P.Hand[3].face=" ";P.Hand[3].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[4].face){P.Hand[4].face=" ";P.Hand[4].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[5].face){P.Hand[5].face=" ";P.Hand[5].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[6].face){P.Hand[6].face=" ";P.Hand[6].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[7].face){P.Hand[7].face=" ";P.Hand[7].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[8].face){P.Hand[8].face=" ";P.Hand[8].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[9].face){P.Hand[9].face=" ";P.Hand[9].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[10].face){P.Hand[10].face=" ";P.Hand[10].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[11].face){P.Hand[11].face=" ";P.Hand[11].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[12].face){P.Hand[12].face=" ";P.Hand[12].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[13].face){P.Hand[13].face=" ";P.Hand[13].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[14].face){P.Hand[14].face=" ";P.Hand[14].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[15].face){P.Hand[15].face=" ";P.Hand[15].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[16].face){P.Hand[16].face=" ";P.Hand[16].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[17].face){P.Hand[17].face=" ";P.Hand[17].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[18].face){P.Hand[18].face=" ";P.Hand[18].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[19].face){P.Hand[19].face=" ";P.Hand[19].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[20].face){P.Hand[20].face=" ";P.Hand[20].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[21].face){P.Hand[21].face=" ";P.Hand[21].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[22].face){P.Hand[22].face=" ";P.Hand[22].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[23].face){P.Hand[23].face=" ";P.Hand[23].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[24].face){P.Hand[24].face=" ";P.Hand[24].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[25].face){P.Hand[25].face=" ";P.Hand[25].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[26].face){P.Hand[26].face=" ";P.Hand[26].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[27].face){P.Hand[27].face=" ";P.Hand[27].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[28].face){P.Hand[28].face=" ";P.Hand[28].suit=" ";P.points++;}
        else if(Draw.face==P.Hand[29].face){P.Hand[29].face=" ";P.Hand[29].suit=" ";P.points++;}
    }
    //otherwise, call insDraw to put drawn card in player's hand array
    else insDraw(P.Hand,Draw);
}
void p2Rqst(Card Hand[],char request[])
{
    //if hand array at index 0 isn't blank, then p2 asks for card in index 0
    if(Hand[0].face!=" ")strcpy(request,Hand[0].face);
    //otherwise if hand array at index 1 isn't blank, then p2 asks for card in index 1.
    else if(Hand[1].face!=" ")strcpy(request,Hand[1].face);
    //otherwise keep searching for a non-blank index
    else if(Hand[2].face!=" ")strcpy(request,Hand[2].face);
    else if(Hand[3].face!=" ")strcpy(request,Hand[3].face);
    else if(Hand[4].face!=" ")strcpy(request,Hand[4].face);
    else if(Hand[5].face!=" ")strcpy(request,Hand[5].face);
    else if(Hand[6].face!=" ")strcpy(request,Hand[6].face);
    else if(Hand[7].face!=" ")strcpy(request,Hand[7].face);
    else if(Hand[8].face!=" ")strcpy(request,Hand[8].face);
    else if(Hand[9].face!=" ")strcpy(request,Hand[9].face);
    else if(Hand[10].face!=" ")strcpy(request,Hand[10].face);
    else if(Hand[11].face!=" ")strcpy(request,Hand[11].face);
    else if(Hand[12].face!=" ")strcpy(request,Hand[12].face);
    else if(Hand[13].face!=" ")strcpy(request,Hand[13].face);
    else if(Hand[14].face!=" ")strcpy(request,Hand[14].face);
    else if(Hand[15].face!=" ")strcpy(request,Hand[15].face);
    else if(Hand[16].face!=" ")strcpy(request,Hand[16].face);
    else if(Hand[17].face!=" ")strcpy(request,Hand[17].face);
    else if(Hand[18].face!=" ")strcpy(request,Hand[18].face);
    else if(Hand[19].face!=" ")strcpy(request,Hand[19].face);
    else if(Hand[20].face!=" ")strcpy(request,Hand[20].face);
    else if(Hand[21].face!=" ")strcpy(request,Hand[21].face);
    else if(Hand[22].face!=" ")strcpy(request,Hand[22].face);
    else if(Hand[23].face!=" ")strcpy(request,Hand[23].face);
    else if(Hand[24].face!=" ")strcpy(request,Hand[24].face);
    else if(Hand[25].face!=" ")strcpy(request,Hand[25].face);
    else if(Hand[26].face!=" ")strcpy(request,Hand[26].face);
    else if(Hand[27].face!=" ")strcpy(request,Hand[27].face);
    else if(Hand[28].face!=" ")strcpy(request,Hand[28].face);
    else if(Hand[29].face!=" ")strcpy(request,Hand[29].face);
    //if all indexes are blank, then return "bypass"
    else strcpy(request,"bypass");
}
bool isEnd(Card Hand1[],Card Hand2[])
{
    bool p1,p2;
    
    p1=isOut(Hand1);
    p2=isOut(Hand2);
    //if every single index in both player's hand arrays are all blank
    if(p1&&p2)
        //return true
        return true;
    //otherwise return false
    else return false;
}
void save(fstream &file,Profile &User,Player &P,int memSize,long cursor)
{
    cout<<"Enter today's date xx/xx/xxxx"<<endl;
    cin.ignore();
    cin.getline(User.date,User.SIZE);
    cout<<User.date<<endl;
    User.hscore=P.points;
    if(cursor==-1)
    {
        
        file.seekp(0L,ios::end);
        file.write(reinterpret_cast<char*>(&User),memSize);
    }
    else
    {
        file.seekp(cursor,ios::beg);
        file.write(reinterpret_cast<char*>(&User),memSize);
    }
    cout<<"Profile saved to file"<<endl;
}
float *hello(fstream &file,float &x,Card *Test)
{
    Test=new Card;
    Test->face=new char[10];
    Test->suit=new char[10];
    Test->face="Joker";
    Test->suit="Joker";
    float *pointer=&x;
    *pointer=*pointer/3;
    file.seekp(0L,ios::beg);
    file.write(reinterpret_cast<char*>(pointer),sizeof(*pointer));
    *pointer=0;
    file.seekg(0L,ios::beg);
    file.read(reinterpret_cast<char*>(pointer),sizeof(*pointer));
    //delete Test;
    return pointer;
}*/