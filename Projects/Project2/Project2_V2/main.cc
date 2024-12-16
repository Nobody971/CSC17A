/*File: main.cpp
 * Author: Anastasia Dettman
 * Created Nov 3rd, 2024
 * Purpose:Go Fish*/

//System Libraries
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

//User Libraries
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Profile.h"

//Global Constants - Math/Science/Conversions/Dimensions

//Function Prototypes
//Deals cards to each player
void deal(Player&,Deck&);
//finds matches in beginning hands
void fndMtch(Player&);
//validates player's card request
void vldt(Player&,char[],const int);
//determines if opposing player has the requested card
bool isMtch(Player&,char[]);
//eliminates match from players' hands and increments points
void winMtch(Player&,Player&,char[]);
//tests if player is out of cards
bool isOut (Player&);
//if match is drawn, scores point and removes cards from hand
void mtchDrw(Player&,Card&);
//determines what card p2 will ask for
void p2Rqst(Player&,char[]);
//tests if both players hands are empty
bool isEnd(Player&,Player&,short);
//begin main function
int main() {
    //set the random number seed based on time
    srand(static_cast<unsigned int>(time(0)));
    
    //variable Declarations
    const int NCARDS=52,//number of cards in a deck, not including jokers
              HAND=30,//size of player hand arrays
              MAX=9;//Max size of cstrings for face values and suits
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
        //call Player constructor function to reset all player attributes after each game
        for(short i=0;i<noPs;i++)
            P[i].Player();
        //assign each player a number
        for(int i=1;i<=noPs;i++)
            P[i].setNo(i);
        
        //display opening message
        cout<<"GO FISH"<<endl;
        cout<<"Remember to always capitalize the first letter of input "<<endl
              "and only input the face value, not the suit"<<endl;
        cout<<"Have fun!"<<endl<<endl;

        //deal 7 cards to each player  
        for(short i=0;i<noPs;i++)
            deal(P[i],Deck1);

        //display message informing player of cards being dealt
        cout<<"Dealing 7 cards to each player..."<<endl;
        //call dspHnd to display player 1's hand
        cout<<"Your cards are"<<endl;
        P[0].dspHnd();
        cout<<endl;
        cout<<endl;
        //call fndMtch to find matches in player 1's hand, 
        //remove matches from hands, and score points
        for(short i=0;i<noPs;i++)
            fndMtch(P[i]);
        //call dspPnts to display all players' points
        for(short i=0;i<noPs;i++)
            cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points."<<endl;
        cout<<endl;

        //BEGIN GAME
        //display begin game message
        cout<<"Begin Game!"<<endl<<endl;
        cout<<"You're Player 1, and Player 1 goes first"<<endl;

        do //do while loop for repeating cycle of turns until all cards are gone       
        {
            //call dspHnd to display p1's cards
            cout<<"Your cards are "<<endl;
            P[0].dspHnd();
            cout<<endl;
            //prompt player to input card request or press x to bypass
            cout<<"Input your card request, or enter x to bypass."<<endl;
            cout<<"Do you have a ";
            //read player's input
            cin.getline(request,MAX);

            //calls vldt to make sure player input properly
            vldt(P[0],request,MAX);

            //display bypass message if player inputs x
            if(strcmp(request,"x")==0)cout<<"You bypassed your turn."<<endl;

            do//do while loop so Player 1 gets another turn if player 2 has requested card
            {
                //call isMtch to return true if player 2 has requested card
                match=isMtch(P[1],request);
                //begin if statement for if isMtch returned true
                if (match)
                {
                    //call winMtch to eliminate match from players' hands and increment points
                    winMtch(P[0],P[1],request);

                    //call isOut to test if player 1's hand array is all blanks.
                    //returns true if so
                    out=isOut(P[0]);

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
                            if(Deck1->getDrws()<NCARDS)
                            {
                                //call goFish to draw card
                                Draw=Deck1->Draw();
                                //display card
                                cout<<"Draw "<<(i+1)<<" is the "<<Draw.dspCard()<<endl;
                                //put card in 1st spot of p1's hand array
                                P[0].insCard(Draw);
                            }
                            //if no cards left in deck, say so on display
                            else cout<<"No more cards left in deck"<<endl;
                        }//end for loop

                        //call fndMtch to remove any matches in these cards and score points
                        fndMtch(P[0]);
                    }//end if statement for player running out of cards

                    //repeat exact process for player 2 running out of cards
                    out=isOut(P[1]);
                    if(out)
                    {
                        cout<<"Player 2 just ran out of cards. "
                              "Player 2 draws three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(Deck1->getDrws()<NCARDS)
                            {
                                P[1].insCard(Deck1->Draw());
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P[1]);
                    }

                    
                    //call dspPnts to display player 1's points
                    for(short i=0;i<noPs;i++)
                        cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points."<<endl;
                    //display that player 1 gets another turn
                    cout<<endl<<"You get another turn! :D"<<endl;
                    cout<<"Your cards are "<<endl;
                    //call dspHnd to display contents of player 1's hand array
                    P[0].dspHnd();
                    cout<<endl;
                    //prompt player to input new card request
                    cout<<"Input your card request, or input x to bypass"<<endl;
                    cout<<"Do you have a ";
                    //read input for card request
                    cin.getline(request,MAX);

                    //call vldt input to make sure player only asks for 
                    //qualifying cards and to eliminate typos
                    vldt(P[0],request,MAX);
                    //if player enters x, display that turn has been bypassed
                    if(request=="x")cout<<"You bypass your turn"<<endl<<endl;

                    //call isMtch to test if opposing player has requested card
                    match=isMtch(P[1],request);
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
                if(Deck1->getDrws<NCARDS)
                {
                    //if true, then calls goFish and sets drawn card variable equal
                    //to the card that function returns
                    Draw=Deck1->Draw();
                    //display drawn card
                    cout<<"You drew the "<<Draw.dspCard()<<endl;

                    //call mtchDrw to determine if player already has drawn card, 
                    //remove matching card from hand and score points.
                    //Otherwise, insert draw into players hand
                    mtchDrw(P[0],Draw);

                    //repeat exact process for testing if player 1 ran out of cards
                    //and drawing three cards
                    out=isOut(P[0]);
                    if(out)
                    { 
                        cout<<"You just ran out of cards. "
                              "Draw three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(Deck1->getDrws()<NCARDS)
                            {
                                Draw=Deck1->Draw();
                                cout<<"Draw "<<(i+1)<<" is the "<<Draw.dspCard()<<endl;
                                P[0].insCard(Draw);
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P[0]);
                    }               
                }
                else cout<<"No more cards left in deck"<<endl;

                //call dspPnts again to display both players points
                for(short i=0;i<noPs;i++)
                    cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points"<<endl;
                cout<<endl;
            }//end of if statement for if isMtch returns false and player didn't bypass

            //PLAYER 2'S TURN
            //announce beginning of player 2's turn on display
            cout<<"Player 2's turn"<<endl;
            cout<<"You're cards are "<<endl;
            //call dspHnd to display contents of p1 hand array
            P[0].dspHnd();
            cout<<endl;

            //call p2Rqust to determine what card p2 will ask for.
            //function returns bypass if p2 hand array is empty
            p2Rqst(P[1],request);

            //remainder of turn is exactly like p1's turn, but variables//arrays
            //for p2 are passed into functions, and p2Rqst is called in 
            //exchange for reading input from player
            if(strcmp(request,"bypass")!=0)
            {
                cout<<"Do you have a "<<request<<"?"<<endl;

                do
                {
                    match=isMtch(P[0],request);
                    if (match)
                    {
                        winMtch(P[1],P[0],request);
                        out=isOut(P[0]);  
                        if(out)
                        {
                            cout<<"You just ran out of cards. "
                                  "Draw three from the deck"<<endl;
                            for(int i=0;i<3;i++)
                            {
                                if(Deck1->getDrws()<NCARDS)
                                {
                                    Draw=Deck1->Draw();
                                    cout<<"Draw "<<(i+1)<<" is the "<<Draw.dspCard();
                                    P[0].insCard(Draw);
                                }
                                else cout<<"No more cards left in deck"<<endl;
                            }
                            fndMtch(P[0]);
                        }
                        out=isOut(P[1]);  
                        if(out)
                        {
                            cout<<"Player 2 just ran out of cards. "
                                  "Player 2 draws three from the deck"<<endl;
                            for(int i=0;i<3;i++)
                            {
                                if(Deck1->getDrws()<NCARDS)
                                {
                                    P[1].insCard(Deck1->Draw());
                                }
                                else cout<<"No more cards left in deck"<<endl;
                            }
                            fndMtch(P[1]);
                        }
                        for(short i=0;i<noPs;i++)
                            cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points"<<endl;
                        cout<<endl<<"Player 2 gets another turn"<<endl;
                        cout<<"Your cards are "<<endl;                
                        P[0].dspHnd();
                        cout<<endl;
                        p2Rqst(P[1],request);

                        if(strcmp(request,"bypass")!=0)
                            cout<<"Do you have a "<<request<<endl;
                        else
                            cout<<"Player two is out of cards and bypasses turn."<<endl<<endl;

                        match=isMtch(P[0],request);
                    }
                }
                while(match);
            }
            else cout<<"Player 2 is out of cards and bypasses turn."<<endl<<endl;

            if ((!match)&&strcmp(request,"bypass")!=0)
            {
                cout<<"Go Fish! Draw a card!"<<endl;
                if(Deck1->getDrws()<NCARDS)
                {
                    Draw=Deck1->Draw();
                    cout<<"Player 2 drew a card."<<endl;
                    mtchDrw(P[1],Draw);
                    out=isOut(P[1]);
                    if(out)
                    {
                        cout<<"Player 2 just ran out of cards. "
                              "Player 2 draws three from the deck"<<endl;
                        for(int i=0;i<3;i++)
                        {
                            if(Deck1->getDrws()<NCARDS)
                            {
                                P[1].insCard(Deck1->Draw());
                            }
                            else cout<<"No more cards left in deck"<<endl;
                        }
                        fndMtch(P[1]);
                    }
                }
                else cout<<"No more cards left in deck"<<endl;

                for(short i=0;i<noPs;i++)
                    cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points"<<endl;
                //announce end of p2's turn on display
                cout<<"End of Player 2's turn."<<endl<<endl;
            }
            //call isEnd to test if both player's hands are empty
            end=isEnd(P[0],P[1],noPs);
        }
        //end of do while loop. Cycle of turns repeats if isEnd returns false
        while(!(end));

        //Announce end of game
        cout<<"No more cards left in the deck"<<endl;
        cout<<"and no more cards left in either players hands."<<endl;
        cout<<"The game is over."<<endl;
        
        //call dspPnts again to display each player's points
        for(short i=0;i<noPs;i++)
            cout<<"Player "<<P[i].getNo()<<" has "<<P[i].getPnts()<<" points"<<endl;
        cout<<endl;

        //test if p1 has more points
        win=P[0].getPnts()>P[1].getPnts();

        //if true
        if (win)
        {   //announce p1 is winner
            cout<<"YOU ARE THE WINNER!!! YIPPEE! WOOHOO!"<<endl<<endl;
        }//otherwise if p1 points = p2 points
        else if (P[0].getPnts()==P[1].getPnts())
        {   //announce a tie
            cout<<"It's a tie! Nobody wins."
                  " You're all a bunch of losers"<<endl<<endl;           
        }//otherwise
        else
        {   //announce p1 loses
            cout<<"LOOOOOOOOOSER!!! Player 2 wins!"<<endl<<endl;
        }
        
        //SAVE/UPDATE PLAYER PROFILE
        if(Profile.getLctn()!=-1)
        {
            if(P[0].getPnts()<=User.getScr())
            {
                cout<<"Your score:      "<<P[0].getPnts()<<endl;
                cout<<"Your high score: "<<User.getScr()<<endl;
            }
            else
            {
                cout<<"New high score!"<<endl;
                User.setScr(P[0].getPnts());
                User.save(User);
            }
        }
        else if(option3!='n'||option3!='N')
        {
            cout<<"Would you like to save your username and score? y for yes and n for no";
            cin.get(option4);
            if(option4=='y'||option4=='Y')User.save(User);
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
    
    //display end of game
    cout<<"Thanks for playing"<<endl;
    cout<<"END OF GAME";

//exit stage right
return 0; }

void deal(Player &P,Deck &Deck1)
{   
    //i=0, loop while i<7, increment i and # of draws after each execution
    for(int i=0;i<7;i++)
    {   //(contents of hand array at index #i) = (card drawn from deck)
        P.insCard(Deck.Draw());
    }
}
void fndMtch(Player &P)
{   //if hand array contents at index 0 = contents at index 1, 
    //(and index 0 isn't blank) set both indexes to blank and increment points 
    //by 1. announce what cards matched
    if(strcmp(P.getFace(0),P.getFace(1))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setPnts(P.getPnts()+1);
    }
    //otherwise if index 0 = index 2 then do the same to these indexes instead
    else if(strcmp(P.getFace(0),P.getFace(2))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setPnts(P.getPnts()+1);
    }
    //otherwise if index 0 = index 3 etc. etc. etc.
    else if(strcmp(P.getFace(0),P.getFace(3))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(4))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(5))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(6))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ");
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }
    //if index 1 = index 2 then do the same. Repeat this process until all cards
    //from indexes 0-7 have been tested for matches
    if(strcmp(P.getFace(1),P.getFace(2))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(3))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(4))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(5))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(6))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(2),P.getFace(3))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(4))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(5))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(6))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(3),P.getFace(4))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(3),P.getFace(5))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(3),P.getFace(6))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(4),P.getFace(5))==0&&(strcmp(P.getFace(4)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(4)<<((strcmp(P.getFace(4),"Six"))==0?"es! ":"s! ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(4),P.getFace(6))==0&&(strcmp(P.getFace(4)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(4)<<((strcmp(P.getFace(4),"Six"))==0?"es! ":"s! ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(5),P.getFace(6))==0&&(strcmp(P.getFace(5)," ")!=0))
    {
        cout<<"Player "<<P.getNo()<<" has two "<<P.getFace(5)<<((strcmp(P.getFace(5),"Six"))==0?"es! ":"s! ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }
}
void vldt(Player &P,char request[],const int MAX)
{
    //while input doesn't match anything in the player hand array AND input 
    //isn't x (x means bypass)
    while(!(strcmp(request,P.getFace((0)))==0||strcmp(request,P.getFace((1)))==0||
            strcmp(request,P.getFace((2)))==0||strcmp(request,P.getFace((3)))==0||
            strcmp(request,P.getFace((4)))==0||strcmp(request,P.getFace((5)))==0||
            strcmp(request,P.getFace((6)))==0||strcmp(request,P.getFace((7)))==0||
            strcmp(request,P.getFace((8)))==0||strcmp(request,P.getFace((9)))==0||
            strcmp(request,P.getFace((10)))==0||strcmp(request,P.getFace((11)))==0||
            strcmp(request,P.getFace((12)))==0||strcmp(request,P.getFace((13)))==0||
            strcmp(request,P.getFace((14)))==0||strcmp(request,P.getFace((15)))==0||
            strcmp(request,P.getFace((16)))==0||strcmp(request,P.getFace((17)))==0||
            strcmp(request,P.getFace((18)))==0||strcmp(request,P.getFace((19)))==0||
            strcmp(request,P.getFace((20)))==0||strcmp(request,P.getFace((21)))==0||
            strcmp(request,P.getFace((22)))==0||strcmp(request,P.getFace((23)))==0||
            strcmp(request,P.getFace((24)))==0||strcmp(request,P.getFace((25)))==0||
            strcmp(request,P.getFace((26)))==0||strcmp(request,P.getFace((27)))==0||
            strcmp(request,P.getFace((28)))==0||strcmp(request,P.getFace((29)))==0||
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
          strcmp(P.getFace(0)," ")==0&&strcmp(P.getFace(1)," ")==0&&
          strcmp(P.getFace(2)," ")==0&&strcmp(P.getFace(3)," ")==0&&
          strcmp(P.getFace(4)," ")==0&&strcmp(P.getFace(5)," ")==0&&
          strcmp(P.getFace(6)," ")==0&&strcmp(P.getFace(7)," ")==0&&
          strcmp(P.getFace(8)," ")==0&&strcmp(P.getFace(9)," ")==0&&
          strcmp(P.getFace(10)," ")==0&&strcmp(P.getFace(11)," ")==0&&
          strcmp(P.getFace(12)," ")==0&&strcmp(P.getFace(13)," ")==0&&
          strcmp(P.getFace(14)," ")==0&&strcmp(P.getFace(15)," ")==0&&
          strcmp(P.getFace(16)," ")==0&&strcmp(P.getFace(17)," ")==0&&
          strcmp(P.getFace(18)," ")==0&&strcmp(P.getFace(19)," ")==0&&
          strcmp(P.getFace(20)," ")==0&&strcmp(P.getFace(21)," ")==0&&
          strcmp(P.getFace(22)," ")==0&&strcmp(P.getFace(23)," ")==0&&
          strcmp(P.getFace(24)," ")==0&&strcmp(P.getFace(25)," ")==0&&
          strcmp(P.getFace(26)," ")==0&&strcmp(P.getFace(27)," ")==0&&
          strcmp(P.getFace(28)," ")==0&&strcmp(P.getFace(29)," ")==0))
    {
        //prompt for new input
        cout<<"You can't bypass your turn if you still have "
              "cards. Try again."<<endl;
        cout<<"Input card request and press enter"<<endl;
        cout<<"Do you have a ";
        //read new input
        cin.getline(request,MAX);
        if(strcmp(request,"x")!=0)vldt(P,request,MAX);
    }
}
bool isMtch(Player &P,char request[])
{   //if player request = (any of the indexes in opposing players hand array)
    if (strcmp(request,P.getFace(0))==0||strcmp(request,P.getFace(1))==0||
        strcmp(request,P.getFace(2))==0||strcmp(request,P.getFace(3))==0||
        strcmp(request,P.getFace(4))==0||strcmp(request,P.getFace(5))==0||
        strcmp(request,P.getFace(6))==0||strcmp(request,P.getFace(7))==0||
        strcmp(request,P.getFace(8))==0||strcmp(request,P.getFace(9))==0||
        strcmp(request,P.getFace(10))==0||strcmp(request,P.getFace(11))==0||
        strcmp(request,P.getFace(12))==0||strcmp(request,P.getFace(13))==0||
        strcmp(request,P.getFace(14))==0||strcmp(request,P.getFace(15))==0||
        strcmp(request,P.getFace(16))==0||strcmp(request,P.getFace(17))==0||
        strcmp(request,P.getFace(18))==0||strcmp(request,P.getFace(19))==0||
        strcmp(request,P.getFace(20))==0||strcmp(request,P.getFace(21))==0||
        strcmp(request,P.getFace(22))==0||strcmp(request,P.getFace(23))==0||
        strcmp(request,P.getFace(24))==0||strcmp(request,P.getFace(25))==0||
        strcmp(request,P.getFace(26))==0||strcmp(request,P.getFace(27))==0||
        strcmp(request,P.getFace(28))==0||strcmp(request,P.getFace(29))==0)
    {
        return true;
    }
    else return false;
}
void winMtch(Player &Asker,Player &Asked,char request[])
{
    //announce that won point and that match was found
    cout<<"Player "<<Asker.getNo()<<" wins a match and scores a point! The matching cards are "
                  "removed from both hands"<<endl;
    //increment player points by one
    Asker.setPnts(Asker.getPnts()+1);

    //for first player, if (hand array index 0) = requested card, hand array 
    //index 0 = blank
    if(strcmp(Asker.getFace(0),request)==0){Asker.setFace(0," ");Asker.setSuit(0," ");}
    //otherwise if (hand array index 1) = requested card, hand array index 0 = blank.
    //keep repeated for every index of hand array
    else if(strcmp(Asker.getFace(1),request)==0){Asker.setFace(1," ");Asker.setSuit(1," ");}
    else if(strcmp(Asker.getFace(2),request)==0){Asker.setFace(2," ");Asker.setSuit(2," ");}
    else if(strcmp(Asker.getFace(3),request)==0){Asker.setFace(3," ");Asker.setSuit(3," ");}
    else if(strcmp(Asker.getFace(4),request)==0){Asker.setFace(4," ");Asker.setSuit(4," ");}
    else if(strcmp(Asker.getFace(5),request)==0){Asker.setFace(5," ");Asker.setSuit(5," ");}
    else if(strcmp(Asker.getFace(6),request)==0){Asker.setFace(6," ");Asker.setSuit(6," ");}
    else if(strcmp(Asker.getFace(7),request)==0){Asker.setFace(7," ");Asker.setSuit(7," ");}
    else if(strcmp(Asker.getFace(8),request)==0){Asker.setFace(8," ");Asker.setSuit(8," ");}
    else if(strcmp(Asker.getFace(9),request)==0){Asker.setFace(9," ");Asker.setSuit(9," ");}
    else if(strcmp(Asker.getFace(10),request)==0){Asker.setFace(10," ");Asker.setSuit(10," ");}
    else if(strcmp(Asker.getFace(11),request)==0){Asker.setFace(11," ");Asker.setSuit(11," ");}
    else if(strcmp(Asker.getFace(12),request)==0){Asker.setFace(12," ");Asker.setSuit(12," ");}
    else if(strcmp(Asker.getFace(13),request)==0){Asker.setFace(13," ");Asker.setSuit(13," ");}
    else if(strcmp(Asker.getFace(14),request)==0){Asker.setFace(14," ");Asker.setSuit(14," ");}
    else if(strcmp(Asker.getFace(15),request)==0){Asker.setFace(15," ");Asker.setSuit(15," ");}
    else if(strcmp(Asker.getFace(16),request)==0){Asker.setFace(16," ");Asker.setSuit(16," ");}
    else if(strcmp(Asker.getFace(17),request)==0){Asker.setFace(17," ");Asker.setSuit(17," ");}
    else if(strcmp(Asker.getFace(18),request)==0){Asker.setFace(18," ");Asker.setSuit(18," ");}
    else if(strcmp(Asker.getFace(19),request)==0){Asker.setFace(19," ");Asker.setSuit(19," ");}
    else if(strcmp(Asker.getFace(20),request)==0){Asker.setFace(20," ");Asker.setSuit(20," ");}
    else if(strcmp(Asker.getFace(21),request)==0){Asker.setFace(21," ");Asker.setSuit(21," ");}
    else if(strcmp(Asker.getFace(22),request)==0){Asker.setFace(22," ");Asker.setSuit(22," ");}
    else if(strcmp(Asker.getFace(23),request)==0){Asker.setFace(23," ");Asker.setSuit(23," ");}
    else if(strcmp(Asker.getFace(24),request)==0){Asker.setFace(24," ");Asker.setSuit(24," ");}
    else if(strcmp(Asker.getFace(25),request)==0){Asker.setFace(25," ");Asker.setSuit(25," ");}
    else if(strcmp(Asker.getFace(26),request)==0){Asker.setFace(26," ");Asker.setSuit(26," ");}
    else if(strcmp(Asker.getFace(27),request)==0){Asker.setFace(27," ");Asker.setSuit(27," ");}
    else if(strcmp(Asker.getFace(28),request)==0){Asker.setFace(28," ");Asker.setSuit(28," ");}
    else if(strcmp(Asker.getFace(29),request)==0){Asker.setFace(29," ");Asker.setSuit(29," ");}

    //repeat process for second player
    if(strcmp(Asked.getFace(0),request)==0){Asked.setFace(0," ");Asked.setSuit(0," ");}
    if(strcmp(Asked.getFace(1),request)==0){Asked.setFace(1," ");Asked.setSuit(1," ");}
    if(strcmp(Asked.getFace(2),request)==0){Asked.setFace(2," ");Asked.setSuit(2," ");}
    if(strcmp(Asked.getFace(3),request)==0){Asked.setFace(3," ");Asked.setSuit(3," ");}
    if(strcmp(Asked.getFace(4),request)==0){Asked.setFace(4," ");Asked.setSuit(4," ");}
    if(strcmp(Asked.getFace(5),request)==0){Asked.setFace(5," ");Asked.setSuit(5," ");}
    if(strcmp(Asked.getFace(6),request)==0){Asked.setFace(6," ");Asked.setSuit(6," ");}
    if(strcmp(Asked.getFace(7),request)==0){Asked.setFace(7," ");Asked.setSuit(7," ");}
    if(strcmp(Asked.getFace(8),request)==0){Asked.setFace(8," ");Asked.setSuit(8," ");}
    if(strcmp(Asked.getFace(9),request)==0){Asked.setFace(9," ");Asked.setSuit(9," ");}
    if(strcmp(Asked.getFace(10),request)==0){Asked.setFace(10," ");Asked.setSuit(10," ");}
    if(strcmp(Asked.getFace(11),request)==0){Asked.setFace(11," ");Asked.setSuit(11," ");}
    if(strcmp(Asked.getFace(12),request)==0){Asked.setFace(12," ");Asked.setSuit(12," ");}
    if(strcmp(Asked.getFace(13),request)==0){Asked.setFace(13," ");Asked.setSuit(13," ");}
    if(strcmp(Asked.getFace(14),request)==0){Asked.setFace(14," ");Asked.setSuit(14," ");}
    if(strcmp(Asked.getFace(15),request)==0){Asked.setFace(15," ");Asked.setSuit(15," ");}
    if(strcmp(Asked.getFace(16),request)==0){Asked.setFace(16," ");Asked.setSuit(16," ");}
    if(strcmp(Asked.getFace(17),request)==0){Asked.setFace(17," ");Asked.setSuit(17," ");}
    if(strcmp(Asked.getFace(18),request)==0){Asked.setFace(18," ");Asked.setSuit(18," ");}
    if(strcmp(Asked.getFace(19),request)==0){Asked.setFace(19," ");Asked.setSuit(19," ");}
    if(strcmp(Asked.getFace(20),request)==0){Asked.setFace(20," ");Asked.setSuit(20," ");}
    if(strcmp(Asked.getFace(21),request)==0){Asked.setFace(21," ");Asked.setSuit(21," ");}
    if(strcmp(Asked.getFace(22),request)==0){Asked.setFace(22," ");Asked.setSuit(22," ");}
    if(strcmp(Asked.getFace(23),request)==0){Asked.setFace(23," ");Asked.setSuit(23," ");}
    if(strcmp(Asked.getFace(24),request)==0){Asked.setFace(24," ");Asked.setSuit(24," ");}
    if(strcmp(Asked.getFace(25),request)==0){Asked.setFace(25," ");Asked.setSuit(25," ");}
    if(strcmp(Asked.getFace(26),request)==0){Asked.setFace(26," ");Asked.setSuit(26," ");}
    if(strcmp(Asked.getFace(27),request)==0){Asked.setFace(27," ");Asked.setSuit(27," ");}
    if(strcmp(Asked.getFace(28),request)==0){Asked.setFace(28," ");Asked.setSuit(28," ");}
    if(strcmp(Asked.getFace(29),request)==0){Asked.setFace(29," ");Asked.setSuit(29," ");}
}
bool isOut (Player &P)
{
    //if every index of hand array = blank
    if(strcmp(P.getFace(0)," ")==0&&strcmp(P.getFace(1)," ")==0&&
       strcmp(P.getFace(2)," ")==0&&strcmp(P.getFace(3)," ")==0&&
       strcmp(P.getFace(4)," ")==0&&strcmp(P.getFace(5)," ")==0&&
       strcmp(P.getFace(6)," ")==0&&strcmp(P.getFace(7)," ")==0&&
       strcmp(P.getFace(8)," ")==0&&strcmp(P.getFace(9)," ")==0&&
       strcmp(P.getFace(10)," ")==0&&strcmp(P.getFace(11)," ")==0&&
       strcmp(P.getFace(12)," ")==0&&strcmp(P.getFace(13)," ")==0&&
       strcmp(P.getFace(14)," ")==0&&strcmp(P.getFace(15)," ")==0&&
       strcmp(P.getFace(16)," ")==0&&strcmp(P.getFace(17)," ")==0&&
       strcmp(P.getFace(18)," ")==0&&strcmp(P.getFace(19)," ")==0&&
       strcmp(P.getFace(20)," ")==0&&strcmp(P.getFace(21)," ")==0&&
       strcmp(P.getFace(22)," ")==0&&strcmp(P.getFace(23)," ")==0&&
       strcmp(P.getFace(24)," ")==0&&strcmp(P.getFace(25)," ")==0&&
       strcmp(P.getFace(26)," ")==0&&strcmp(P.getFace(27)," ")==0&&
       strcmp(P.getFace(28)," ")==0&&strcmp(P.getFace(29)," ")==0)
    {
        //return true
        return true;
    }
    //otherwise return false
    else return false;
}
void mtchDrw(Player &P,Card &Draw)
{
    //if drawn card = (any of the indexes in hand array)
    if(strcmp(Draw.getFace(),P.getFace(0))==0||strcmp(Draw.getFace(),P.getFace(1))==0||
       strcmp(Draw.getFace(),P.getFace(2))==0||strcmp(Draw.getFace(),P.getFace(3))==0||
       strcmp(Draw.getFace(),P.getFace(4))==0||strcmp(Draw.getFace(),P.getFace(5))==0||
       strcmp(Draw.getFace(),P.getFace(6))==0||strcmp(Draw.getFace(),P.getFace(7))==0||
       strcmp(Draw.getFace(),P.getFace(8))==0||strcmp(Draw.getFace(),P.getFace(9))==0||
       strcmp(Draw.getFace(),P.getFace(10))==0||strcmp(Draw.getFace(),P.getFace(11))==0||
       strcmp(Draw.getFace(),P.getFace(12))==0||strcmp(Draw.getFace(),P.getFace(13))==0||
       strcmp(Draw.getFace(),P.getFace(14))==0||strcmp(Draw.getFace(),P.getFace(15))==0||
       strcmp(Draw.getFace(),P.getFace(16))==0||strcmp(Draw.getFace(),P.getFace(17))==0||
       strcmp(Draw.getFace(),P.getFace(18))==0||strcmp(Draw.getFace(),P.getFace(19))==0||
       strcmp(Draw.getFace(),P.getFace(20))==0||strcmp(Draw.getFace(),P.getFace(21))==0||
       strcmp(Draw.getFace(),P.getFace(22))==0||strcmp(Draw.getFace(),P.getFace(23))==0||
       strcmp(Draw.getFace(),P.getFace(24))==0||strcmp(Draw.getFace(),P.getFace(25))==0||
       strcmp(Draw.getFace(),P.getFace(26))==0||strcmp(Draw.getFace(),P.getFace(27))==0||
       strcmp(Draw.getFace(),P.getFace(28))==0||strcmp(Draw.getFace(),P.getFace(29))==0)
    {
        //announce the found match and won point
        cout<<"Player "<<P.getNo()<<" has two "<<Draw.getFace()<<(strcmp(Draw.getFace(),"Six")==0?"es! ":"s! ");
        cout<<"Player "<<P.getNo()<<" wins a point!"<<endl;
        //if drawn card = (index 0 of hand array), then index 0 = blank.
        //increment points by 1
        if(strcmp(Draw.getFace(),P.getFace(0))==0){P.setFace(0," ");P.setSuit(0," ");P.setPnts(P.getPnts()+1);}
        //otherwise if drawn card = (index 1 of hand array), then index 1 = blank.
        //increment points by 1
        else if(strcmp(Draw.getFace(),P.getFace(1))==0){P.setFace(1," ");P.setSuit(1," ");P.setPnts(P.getPnts()+1);}
        //keep testing until the index with matching card is found
        else if(strcmp(Draw.getFace(),P.getFace(2))==0){P.setFace(2," ");P.setSuit(2," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(3))==0){P.setFace(3," ");P.setSuit(3," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(4))==0){P.setFace(4," ");P.setSuit(4," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(5))==0){P.setFace(5," ");P.setSuit(5," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(6))==0){P.setFace(6," ");P.setSuit(6," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(7))==0){P.setFace(7," ");P.setSuit(7," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(8))==0){P.setFace(8," ");P.setSuit(8," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(9))==0){P.setFace(9," ");P.setSuit(9," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(10))==0){P.setFace(10," ");P.setSuit(10," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(11))==0){P.setFace(11," ");P.setSuit(11," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(12))==0){P.setFace(12," ");P.setSuit(12," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(13))==0){P.setFace(13," ");P.setSuit(13," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(14))==0){P.setFace(14," ");P.setSuit(14," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(15))==0){P.setFace(15," ");P.setSuit(15," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(16))==0){P.setFace(16," ");P.setSuit(16," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(17))==0){P.setFace(17," ");P.setSuit(17," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(18))==0){P.setFace(18," ");P.setSuit(18," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(19))==0){P.setFace(19," ");P.setSuit(19," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(20))==0){P.setFace(20," ");P.setSuit(20," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(21))==0){P.setFace(21," ");P.setSuit(21," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(22))==0){P.setFace(22," ");P.setSuit(22," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(23))==0){P.setFace(23," ");P.setSuit(23," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(24))==0){P.setFace(24," ");P.setSuit(24," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(25))==0){P.setFace(25," ");P.setSuit(25," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(26))==0){P.setFace(26," ");P.setSuit(26," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(27))==0){P.setFace(27," ");P.setSuit(27," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(28))==0){P.setFace(28," ");P.setSuit(28," ");P.setPnts(P.getPnts()+1);}
        else if(strcmp(Draw.getFace(),P.getFace(29))==0){P.setFace(29," ");P.setSuit(29," ");P.setPnts(P.getPnts()+1);}
    }
    //otherwise, call insDraw to put drawn card in player's hand array
    else P.insCard(Draw);
}
void p2Rqst(Player P,char request[])
{
    //if hand array at index 0 isn't blank, then p2 asks for card in index 0
    if(strcmp(P.getFace(0)," ")!=0)strcpy(request,P.getFace(0));
    //otherwise if hand array at index 1 isn't blank, then p2 asks for card in index 1.
    else if(strcmp(P.getFace(1)," ")!=0)strcpy(request,P.getFace(1));
    //otherwise keep searching for a non-blank index
    else if(strcmp(P.getFace(2)," ")!=0)strcpy(request,P.getFace(2));
    else if(strcmp(P.getFace(3)," ")!=0)strcpy(request,P.getFace(3));
    else if(strcmp(P.getFace(4)," ")!=0)strcpy(request,P.getFace(4));
    else if(strcmp(P.getFace(5)," ")!=0)strcpy(request,P.getFace(5));
    else if(strcmp(P.getFace(6)," ")!=0)strcpy(request,P.getFace(6));
    else if(strcmp(P.getFace(7)," ")!=0)strcpy(request,P.getFace(7));
    else if(strcmp(P.getFace(8)," ")!=0)strcpy(request,P.getFace(8));
    else if(strcmp(P.getFace(9)," ")!=0)strcpy(request,P.getFace(9));
    else if(strcmp(P.getFace(10)," ")!=0)strcpy(request,P.getFace(10));
    else if(strcmp(P.getFace(11)," ")!=0)strcpy(request,P.getFace(11));
    else if(strcmp(P.getFace(12)," ")!=0)strcpy(request,P.getFace(12));
    else if(strcmp(P.getFace(13)," ")!=0)strcpy(request,P.getFace(13));
    else if(strcmp(P.getFace(14)," ")!=0)strcpy(request,P.getFace(14));
    else if(strcmp(P.getFace(15)," ")!=0)strcpy(request,P.getFace(15));
    else if(strcmp(P.getFace(16)," ")!=0)strcpy(request,P.getFace(16));
    else if(strcmp(P.getFace(17)," ")!=0)strcpy(request,P.getFace(17));
    else if(strcmp(P.getFace(18)," ")!=0)strcpy(request,P.getFace(18));
    else if(strcmp(P.getFace(19)," ")!=0)strcpy(request,P.getFace(19));
    else if(strcmp(P.getFace(20)," ")!=0)strcpy(request,P.getFace(20));
    else if(strcmp(P.getFace(21)," ")!=0)strcpy(request,P.getFace(21));
    else if(strcmp(P.getFace(22)," ")!=0)strcpy(request,P.getFace(22));
    else if(strcmp(P.getFace(23)," ")!=0)strcpy(request,P.getFace(23));
    else if(strcmp(P.getFace(24)," ")!=0)strcpy(request,P.getFace(24));
    else if(strcmp(P.getFace(25)," ")!=0)strcpy(request,P.getFace(25));
    else if(strcmp(P.getFace(26)," ")!=0)strcpy(request,P.getFace(26));
    else if(strcmp(P.getFace(27)," ")!=0)strcpy(request,P.getFace(27));
    else if(strcmp(P.getFace(28)," ")!=0)strcpy(request,P.getFace(28));
    else if(strcmp(P.getFace(29)," ")!=0)strcpy(request,P.getFace(29));
    //if all indexes are blank, then return "bypass"
    else strcpy(request,"bypass");
}
bool isEnd(Player &P1,Player &P2,short noPs)
{
    bool p1,p2;
    
    p1=isOut(P1);
    p2=isOut(P2);
    //if every single index in both player's hand arrays is blank
    if(p1&&p2)
        //return true
        return true;
    //otherwise return false
    else return false;
}