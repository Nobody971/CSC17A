/*File: main.cpp
 * Author: Anastasia Dettman
 * Created 12/03/2024
 * Purpose:Go Fish*/

//System Libraries
#include <iostream>
#include <iomanip>
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
//Deals 7 cards to specified player
void deal(Player&,Deck*,Card&);
//searches for matches in specified player's hand
void fndMtch(Player&);
//displays all players' points
void dspPnts(Player[],short,short);//displays all players points
//takes specified players name announces start of their turn
void header(char[]);
//validates player's card request
void vldt(Player&,char[],const int,short noPs);
//validates input name and returns index to named player
short vldtNm(Player[],char[],short,short);
//determines if specified player has the requested card
bool isMtch(Player&,char[]);
//commits requested card to computer players memory
void memory(char[],char[],char[],char[],char[],short[],short);
//eliminates found match from both players' hands and increments points
void winMtch(Player&,Player&,char[]);
//tests for if specified player is out of cards and deals three if so
void restock(Player&,Deck*,const short,Card&);
//tests if player is out of cards (called by restock)
bool isOut (Player&);
//if match is drawn, scores point and removes cards from hand
void mtchDrw(Player&,Card&);
//executes specified computer player's turn
void turn(Player[],short,Deck*,char[],short,short,const short,Card&);
//determines what card specified computer player will ask for
void pRqst(Player&,char[]);
//tests if total number of points = 26
bool isEnd(Player[],short);
//returns true if player 1 wins and ranks players from highest to lowest score
template <class T>
bool order(Player[],T,T[],T[]);
//begin main function
int main() {
    //set the random number seed based on time
    srand(static_cast<unsigned int>(time(0)));
    
    //Object Declarations
    Profile User;//holds name date and highscore from previous games
    Card Draw;//temp holding place for drawn cards
    Deck *Deck1=nullptr;//for dynamically creating deck of cards
    Player *P;//for allocating array for specified number of player classes
    const short NCARDS=52,//number of cards in a deck, not including jokers
                MAX=Draw.getSize(Draw);//Max size of cstrings for face values and suits
    char option1,//Y or N for playing again
         option2,//Y or N for creating new profile
         name[User.getSize()],//for reading in computer players name
         request[MAX],//holds face value of card being asked for by player
         mem1[MAX],//cstrings for remembering the past 4 requested cards
         mem2[MAX],
         mem3[MAX],
         mem4[MAX];
    bool win=true,//true if player 1 wins the game
         match,//true if opposing player has the requested card
         out,//true if a player ran out of cards
         end;//true if all players points add up to 26
    short noPs,//for reading in number of players
          asked=1,//player being asked for a card, default is player 2 (a.k.a. P[1])
          *asker,//parallel to mem arrays. Holds p#s
          *scores,//dynamic array for sorting player scores
          *pNums;//dynamic array parallel to scores[], holds player #s
    
    //DISPLAY OPENING MESSAGE
    cout<<"*******************************************************"<<endl;
    cout<<"                       GO FISH"<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"Rules: Goal is to collected pairs of cards with the "<<endl;
    cout<<"same face value. Keep collecting matches until all "<<endl;
    cout<<"the cards in the deck are paired up. Player with the "<<endl;
    cout<<"most matches at the end of the game wins."<<endl;
    cout<<endl;
    cout<<"Syntax: When inputting a card request, only input the "<<endl;
    cout<<"face value, not the suit. Always capitalize the first "<<endl;
    cout<<"letter. Use words, not numbers e.g. Six, Ten, etc. If "<<endl;
    cout<<"there are no cards to draw and you have none in your "<<endl;
    cout<<"hand, input x to bypass your turn."<<endl;
    cout<<"Have fun!"<<endl;
    cout<<"------------------------Login--------------------------"<<endl;
    //CREATE/FIND PLAYER PROFILE
    User.inputNm();
    do//loops as long as player inputs y to starting new game
    {
        //determine number of opponents
        cout<<"How many opponents do you want? Input integer 1-6."<<endl;
        cin>>noPs;
        //can't have less than 1 or more than six opponents
        while(noPs<1||noPs>6)
        {
            cout<<"Try again. Input integer 1-6."<<endl;
            cin>>noPs;
        }
        cin.ignore();
        //noPs needs to include User
        noPs++;
        //create array of players to be deleted after each game
        P=new Player[noPs];
        //create arrays dependent on no of players
        asker=new short[noPs];
        scores=new short[noPs];
        pNums=new short[noPs];
        //create deck of cards to be deleted/reset after each game
        Deck1=new Deck;
        //set player options to x at the beginning of each game
        option1='x';
        option2='x';
        //reset asked to default
        asked=1;
        //assign each player a number
        for(int i=0;i<noPs;i++)
            P[i].setNo(i+1);
        //names player 1 after their profile name
        User.copyNm(P[0].getName());
        //reads input for each computer players name
        for(short i=1;i<noPs;i++)
        {
            cout<<"Give Player "<<P[i].getNo()<<" a name. "<<User.getSize()-1<<" characters max."<<endl;
            cin.getline(name,User.getSize());
            P[i].setName(name);
        }
        //BEGIN GAME
        //display begin game message
        cout<<"*******************************************************"<<endl;
        cout<<"                       Begin Game!"<<endl;
        cout<<"*******************************************************"<<endl;
        //deal 7 cards to each player  
        for(short i=0;i<noPs;i++)
            deal(P[i],Deck1,Draw);
        cout<<"Dealing 7 cards to each player..."<<endl;
        //Display player 1's hand
        cout<<"Your cards are"<<endl;
        P[0].dspHnd();
        //Find any matches in players beginning hands and increment points
        //accordingly
        for(short i=0;i<noPs;i++)
            fndMtch(P[i]);
        //Display all players' points
        dspPnts(P,noPs,User.getSize());

        //BEGIN CYCLE OF TURNS
        do //do while loop for repeating cycle of turns until all cards are paired up
        {   //announce player 1's turn
            header(P[0].getName());
            do
            {   //Display p1's cards
                cout<<"Your cards are "<<endl;
                P[0].dspHnd();
                //prompt player to input card request
                cout<<"Input your card request, or enter x to bypass."<<endl;
                cout<<"Do you have a ";
                //read player's input
                cin.getline(request,MAX);

                //Validate input
                vldt(P[0],request,MAX,noPs);
                //only continue turn if player didn't bypass
                if(strcmp(request,"x")!=0)
                {   //only prompt for name if there's more than 1 opponent
                    if(noPs>2)
                    {   //prompt user to specify who they're asking
                        cout<<"Who do you want to ask?"<<endl;
                        cin.getline(name,User.getSize());
                        //Use name to find players number and validate name
                        asked=vldtNm(P,name,noPs,User.getSize());
                    }
                    //call isMtch to return true if opponent has requested card
                    match=isMtch(P[asked],request);
                    //if match, then remove match increment points
                    if (match)
                    {   //call winMtch to eliminate match from players' hands and increment points
                        winMtch(P[0],P[asked],request);
                        //test if player 1 in out of cards
                        out=isOut(P[0]);
                        //deal three if true
                        if(out){restock(P[0],Deck1,NCARDS,Draw);}
                        //repeat for if opponent is out of cards
                        out=isOut(P[asked]);
                        if(out){restock(P[asked],Deck1,NCARDS,Draw);}
                        //Display all players' points
                        dspPnts(P,noPs,User.getSize());
                        //display that player 1 gets another turn
                        cout<<"You get another turn! :D"<<endl;
                    }
                }else cout<<"You bypassed your turn"<<endl;
            }//if isMtch returns true and player didn't bypass, then repeat do while loop
            while(match&&strcmp(request,"x")!=0);

            //if statement for when isMtch returns false and the player didn't bypass
            if (!(match)&&strcmp(request,"x")!=0)
            {   //commit requested card to memory
                //memory(request,mem1,mem2,mem3,mem4,asker,0);
                //display 'go fish, draw a card'
                cout<<"Go Fish! Draw a card!"<<endl;

                //if statement that tests if number of cards drawn is less than
                //total number of cards
                if(Deck1->getDrws()<NCARDS)
                {
                    //if true, then calls goFish and sets drawn card variable equal
                    //to the card that function returns
                    Draw=Deck1->Draw();
                    //display drawn card
                    cout<<"You drew the ";
                    Draw.dspCard();
                    cout<<endl;

                    //call mtchDrw to determine if player already has drawn card, 
                    //remove matching card from hand and score points.
                    //Otherwise, insert draw into players hand
                    mtchDrw(P[0],Draw);

                    //call isOut to test if player 1's hand array is all blanks.
                    //returns true if so
                    out=isOut(P[0]);
                    if(out){restock(P[0],Deck1,NCARDS,Draw);}     
                }
                else cout<<"No more cards left in deck"<<endl;
                //call dspPnts to display all players' points
                dspPnts(P,noPs,User.getSize());
            }
            //COMPUTER PLAYERS TURNS
            for(short i=1;i<noPs;i++)
                turn(P,i,Deck1,request,noPs,User.getSize(),NCARDS,Draw);
            
            //call isEnd to test if both player's hands are empty
            end=isEnd(P,noPs);
        }//end of do while loop. Cycle of turns repeats if isEnd returns false
        while(!(end));

        //Announce end of game
        cout<<"All cards have been paired up! The game is over!"<<endl;
        
        //call dspPnts to display all players' points
        dspPnts(P,noPs,User.getSize());

        //rank players to determine winner
        win=order(P,noPs,scores,pNums);

        //if true
        if (win)
        {   //announce p1 is winner
            cout<<"*******************************************************"<<endl;
            cout<<"          YOU'RE THE WINNER!!! YIPPEE! WOOHOO!"<<endl;
            cout<<"*******************************************************"<<endl;
        }
        cout<<"-----------------------ranking-------------------------"<<endl;
        cout<<"1st place: "<<P[pNums[noPs-1]-1].getName()<<" at "<<scores[noPs-1]<<" points."<<endl;
        cout<<"2nd place: "<<P[pNums[noPs-2]-1].getName()<<" at "<<scores[noPs-2]<<" points."<<endl;
        for(short i=noPs-3,j=3;i>=0;i--,j++)
        {
            cout<<j<<((j==3)?"rd":"th")
                <<" place: "<<P[pNums[i]-1].getName()<<" at "<<scores[i]<<" points."<<endl;
        }
        
        //SAVE/UPDATE PLAYER PROFILE
        cout<<"-----------------------profile-------------------------"<<endl;
        if(User.getLctn()>=0)
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
                try{User.save(User);}
                catch(short x){cout<<"Error during save process."<<endl;return 0;}
            }
        }
        else if(User.getLctn()==-1)
        {
            cout<<"Would you like to save your username and score? y for yes and n for no"<<endl;
            cin.get(option2);
            if(option2=='y'||option2=='Y')
            {
                User.setScr(P[0].getPnts());
                try{User.save(User);}
                catch(short x){cout<<"Error during save process."<<endl;return 0;}
            }
        }
        //display top scores
        User.top5();
        
        //prompt player to input Y to play again or anything else to stop
        cout<<"Would you like to play again? y for yes and n for no"<<endl;
        //read input from player
        cin.get(option1);
        cin.ignore();
        //delete dynamic arays dependant on no of players
        delete []P;
        delete []asker;
        delete []scores;
        delete []pNums;
        //delete deck of cards
        delete Deck1;
    }//end of do while loop. entire game repeats if player inputs Y
    while(option1=='Y'||option1=='y');
    
    //display end of game
    cout<<"Thanks for playing!"<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"                     END OF GAME"<<endl;
    cout<<"*******************************************************"<<endl;
//exit stage right
return 0; }

void deal(Player &P,Deck *Deck1,Card &Draw)
{   
    //i=0, loop while i<7, increment i and # of draws after each execution
    for(int i=0;i<7;i++)
    {   
        Draw=Deck1->Draw();
        P.insCard(Draw);
    }
}
void fndMtch(Player &P)
{   //if hand array contents at index 0 = contents at index 1, 
    //(and index 0 isn't blank) set both indexes to blank and increment points 
    //by 1. announce what cards matched
    if(strcmp(P.getFace(0),P.getFace(1))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setPnts(P.getPnts()+1);
    }
    //otherwise if index 0 = index 2 then do the same to these indexes instead
    else if(strcmp(P.getFace(0),P.getFace(2))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setPnts(P.getPnts()+1);
    }
    //otherwise if index 0 = index 3 etc. etc. etc.
    else if(strcmp(P.getFace(0),P.getFace(3))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(4))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(5))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(0," ");
        P.setSuit(0," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(0),P.getFace(6))==0&&(strcmp(P.getFace(0)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(0)<<((strcmp(P.getFace(0),"Six"))==0?"es! ":"s! ")<<endl;
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
        cout<<P.getName()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(3))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(4))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(5))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(1),P.getFace(6))==0&&(strcmp(P.getFace(1)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(1)<<((strcmp(P.getFace(1),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(1," ");
        P.setSuit(1," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(2),P.getFace(3))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(4))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(5))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(2),P.getFace(6))==0&&(strcmp(P.getFace(2)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(2)<<((strcmp(P.getFace(2),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(2," ");
        P.setSuit(2," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(3),P.getFace(4))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(3),P.getFace(5))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(3),P.getFace(6))==0&&(strcmp(P.getFace(3)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(3)<<((strcmp(P.getFace(3),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(3," ");
        P.setSuit(3," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(4),P.getFace(5))==0&&(strcmp(P.getFace(4)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(4)<<((strcmp(P.getFace(4),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setPnts(P.getPnts()+1);
    }
    else if(strcmp(P.getFace(4),P.getFace(6))==0&&(strcmp(P.getFace(4)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(4)<<((strcmp(P.getFace(4),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(4," ");
        P.setSuit(4," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }

    if(strcmp(P.getFace(5),P.getFace(6))==0&&(strcmp(P.getFace(5)," ")!=0))
    {
        cout<<P.getName()<<" has two "<<P.getFace(5)<<((strcmp(P.getFace(5),"Six"))==0?"es! ":"s! ")<<endl;
        P.setFace(5," ");
        P.setSuit(5," ");
        P.setFace(6," ");
        P.setSuit(6," ");
        P.setPnts(P.getPnts()+1);
    }
}
void dspPnts(Player P[],short noPs,short width)
{
    for(short i=0;i<noPs;i++)
    {
        cout<<setw(width)<<left<<P[i].getName()<<":";
        cout<<right<<P[i].points<<((P[i].points==1)?" point":" points")<<endl;
    }
}
void turn(Player P[],short index,Deck *Deck1,char request[],short noPs,short width,const short NCARDS,Card &Draw)
{
    bool match,out;
    short asked;
    //announce beginning of player's turn on display
    header(P[index].getName());
    cout<<"Your cards are "<<endl;
    //call dspHnd to display contents of p1 hand array
    P[0].dspHnd();

    //call p2Rqust to determine what card p2 will ask for.
    //function returns bypass if p2 hand array is empty
    pRqst(P[index],request);
    do{asked=(rand()%noPs)+1;}while(asked==(index+1));
    if(strcmp(request,"bypass")!=0)
    {
        cout<<P[asked-1].getName()<<", do you have a "<<request<<"?"<<endl;
        do
        {
            match=isMtch(P[asked-1],request);
            if (match)
            {
                winMtch(P[index],P[asked-1],request);
                out=isOut(P[asked-1]);
                if(out){restock(P[asked-1],Deck1,NCARDS,Draw);}
                out=isOut(P[index]);
                if(out){restock(P[index],Deck1,NCARDS,Draw);}
                dspPnts(P,noPs,width);

                cout<<P[index].getName()<<" gets another turn."<<endl;
                cout<<"Your cards are "<<endl;                
                P[0].dspHnd();
                pRqst(P[index],request);
                do{asked=(rand()%noPs)+1;}while(asked==(index+1));
                if(strcmp(request,"bypass")!=0)
                    cout<<P[asked-1].getName()<<", do you have a "<<request<<"?"<<endl;
                else
                    cout<<P[index].getName()<<" is out of cards and bypasses turn."<<endl;

                match=isMtch(P[asked-1],request);
            }
        }
        while(match);
    }
    else cout<<P[index].getName()<<" is out of cards and bypasses turn."<<endl;

    if ((!match)&&strcmp(request,"bypass")!=0)
    {
        //memory(request,mem1,mem2,mem3,mem4,asker,P.getNo());
        cout<<"Go Fish! Draw a card!"<<endl;
        if(Deck1->getDrws()<NCARDS)
        {
            Draw=Deck1->Draw();
            cout<<P[index].getName()<<" drew a card."<<endl;
            mtchDrw(P[index],Draw);
            out=isOut(P[asked-1]);
            if(out){restock(P[asked-1],Deck1,NCARDS,Draw);}
            out=isOut(P[index]);
            if(out){restock(P[index],Deck1,NCARDS,Draw);}
        }
        else cout<<"No more cards left in deck"<<endl;
        dspPnts(P,noPs,width);
    }
}
void header(char n[])
{
    cout<<"***************************************************"<<endl;
    cout<<"                 "<<n<<"'s Turn"<<endl;
    cout<<"***************************************************"<<endl;
}
void vldt(Player &P,char request[],const int MAX,short noPs)
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
        if(strcmp(request,"x")!=0&&noPs>2)vldt(P,request,MAX,noPs);
    }
}
short vldtNm(Player P[],char name[],short noPs,short size)
{
    bool test=false;
    for(short i=1;i<noPs;i++)
    {
        test=(!strcmp(name,P[i].getName()));
        if(test)return i;
    }
    cout<<"Invalid. Try again."<<endl;
    cin.getline(name,size);
    vldtNm(P,name,noPs,size);
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
void memory(char request[],char mem1[],char mem2[],char mem3[],char mem4[],short asker[], short pNo)
{
    if(!strcmp(mem4," ")){strcpy(mem4,request);asker[3]=pNo;}
    else if(!strcmp(mem3," ")){strcpy(mem3,request);asker[2]=pNo;}
    else if(!strcmp(mem2," ")){strcpy(mem2,request);asker[1]=pNo;}
    else if(!strcmp(mem1," ")){strcpy(mem1,request);asker[0]=pNo;}
    else
    {
        strcpy(mem4,mem3);
        strcpy(mem3,mem2);
        strcpy(mem2,mem1);
        strcpy(mem1,request);
        asker[3]=asker[2];
        asker[2]=asker[1];
        asker[1]=asker[0];
        asker[0]=pNo;
    }
}
void winMtch(Player &Asker,Player &Asked,char request[])
{
    //announce that won point and that match was found
    cout<<Asker.getName()<<" wins a match and scores a point!"<<endl;
    cout<<"The matching cards are removed from both hands"<<endl;
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
void restock(Player &P,Deck *Deck1,const short NCARDS,Card &Draw)
{   //display message informing player
    if(P.getNo()==1){cout<<"You ran of of cards! Draw three from the deck."<<endl;}
    else{cout<<P.getName()<<" runs out of cards and draws three from the deck."<<endl;}
    //for loop that executes 3 times for 3 cards
    for(int i=0;i<3;i++)
    {   //if no of draws < no of cards in deck
        if(Deck1->getDrws()<NCARDS)
        {   //call Draw to draw card
            Draw=Deck1->Draw();
            //display card
            if(P.getNo()==1)
            {
                cout<<"Draw "<<(i+1)<<" is the ";
                Draw.dspCard();
                cout<<endl;
            }
            //put card in 1st spot of p1's hand array
            P.insCard(Draw);
        }
        //if no cards left in deck, say so on display
        else cout<<"No more cards left in deck"<<endl;
    }//end for loop
    //call fndMtch to remove any matches in these cards and score points
    fndMtch(P);
    //end if statement for player running out of cards
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
    if(Draw==P.getCard(0)||Draw==P.getCard(1)||Draw==P.getCard(2)||
       Draw==P.getCard(3)||Draw==P.getCard(4)||Draw==P.getCard(5)||
       Draw==P.getCard(6)||Draw==P.getCard(7)||Draw==P.getCard(8)||
       Draw==P.getCard(9)||Draw==P.getCard(10)||Draw==P.getCard(11)||
       Draw==P.getCard(12)||Draw==P.getCard(13)||Draw==P.getCard(14)||
       Draw==P.getCard(15)||Draw==P.getCard(16)||Draw==P.getCard(17)||
       Draw==P.getCard(18)||Draw==P.getCard(19)||Draw==P.getCard(20)||
       Draw==P.getCard(21)||Draw==P.getCard(22)||Draw==P.getCard(23)||
       Draw==P.getCard(24)||Draw==P.getCard(25)||Draw==P.getCard(26)||
       Draw==P.getCard(27)||Draw==P.getCard(28)||Draw==P.getCard(29))
    {
        //announce the found match and won point
        cout<<P.getName()<<" has two "<<Draw.getFace()<<(strcmp(Draw.getFace(),"Six")==0?"es! ":"s! ");
        cout<<P.getName()<<" wins a point!"<<endl;
        //if drawn card = (index 0 of hand array), then index 0 = blank.
        //increment points by 1
        if(Draw==P.getCard(0)){P.setFace(0," ");P.setSuit(0," ");P.setPnts(P.getPnts()+1);}
        //otherwise if drawn card = (index 1 of hand array), then index 1 = blank.
        //increment points by 1
        else if(Draw==P.getCard(1)){P.setFace(1," ");P.setSuit(1," ");P.setPnts(P.getPnts()+1);}
        //keep testing until the index with matching card is found
        else if(Draw==P.getCard(2)){P.setFace(2," ");P.setSuit(2," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(3)){P.setFace(3," ");P.setSuit(3," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(4)){P.setFace(4," ");P.setSuit(4," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(5)){P.setFace(5," ");P.setSuit(5," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(6)){P.setFace(6," ");P.setSuit(6," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(7)){P.setFace(7," ");P.setSuit(7," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(8)){P.setFace(8," ");P.setSuit(8," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(9)){P.setFace(9," ");P.setSuit(9," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(10)){P.setFace(10," ");P.setSuit(10," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(11)){P.setFace(11," ");P.setSuit(11," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(12)){P.setFace(12," ");P.setSuit(12," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(13)){P.setFace(13," ");P.setSuit(13," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(14)){P.setFace(14," ");P.setSuit(14," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(15)){P.setFace(15," ");P.setSuit(15," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(16)){P.setFace(16," ");P.setSuit(16," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(17)){P.setFace(17," ");P.setSuit(17," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(18)){P.setFace(18," ");P.setSuit(18," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(19)){P.setFace(19," ");P.setSuit(19," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(20)){P.setFace(20," ");P.setSuit(20," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(21)){P.setFace(21," ");P.setSuit(21," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(22)){P.setFace(22," ");P.setSuit(22," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(23)){P.setFace(23," ");P.setSuit(23," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(24)){P.setFace(24," ");P.setSuit(24," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(25)){P.setFace(25," ");P.setSuit(25," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(26)){P.setFace(26," ");P.setSuit(26," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(27)){P.setFace(27," ");P.setSuit(27," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(28)){P.setFace(28," ");P.setSuit(28," ");P.setPnts(P.getPnts()+1);}
        else if(Draw==P.getCard(29)){P.setFace(29," ");P.setSuit(29," ");P.setPnts(P.getPnts()+1);}
    }
    //otherwise, call insDraw to put drawn card in player's hand array
    else P.insCard(Draw);
}
void pRqst(Player &P,char request[])
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
bool isEnd(Player P[],short noPs)
{
    short total=0;
    for(short i=0;i<noPs;i++)
    {
        total+=P[i].getPnts();
    }
    if(total==26)return true;
    else return false;
}
template <class T>
bool order(Player P[],T noPs,T scores[],T pNums[])
{
    //move player points and player nos to parallel arrays
    for(short i=0;i<noPs;i++)
    {
        pNums[i]=P[i].getNo();
        scores[i]=P[i].getPnts();
    }
    //use Marksort to sort score array while keeping pNums parallel
    for(short i=0;i<noPs-1;i++)
    {
        for(short j=i+1;j<noPs;j++)
        {
            if(scores[j]<scores[i])
            {
                //swap score indexes
                short temp=scores[j];
                scores[j]=scores[i];
                scores[i]=temp;
                //swap player no indexes
                temp=pNums[j];
                pNums[j]=pNums[i];
                pNums[i]=temp;
                
            }
        }
    }
    if(pNums[noPs-1]==P[0].getNo())return true;
    else return false;
}