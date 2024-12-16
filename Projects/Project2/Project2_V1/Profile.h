/* 
 * File:   Profile.h
 * Author: anast
 *
 * Created on November 25, 2024, 5:00 PM
 */

#ifndef PROFILE_H
#define PROFILE_H
#include <iostream>
#include <fstream>

class Profile
{
    private:
        char name[15];
        char date[15];
        short hscore;
        const int SIZE=15;
        long fLctn;//location in file
        Profile();//constructor
        void search();//searches file for entered username;
        ~Profile();//destructor
    public:
        void inputNm();//reads user input for name
};

Profile::Profile()
{
    strcpy(name," ");
    strcpy(date," ");
    hscore=0;
}
void Profile::inputNm()
{
    char option='x';
    do
    {
        cout<<"Please input your username. Max 14 characters."<<endl;
        cin.getline(name,SIZE);
        cout<<name<<", is this correct? y for yes and n for no"<<endl;
                cin.get(option);
                cin.ignore();
    }while(option!='y'&&option!='Y');
    Profile.search();
}
void Profile::search()
{
    fstream file;
    long fSize;
    long cursor;
    char option='x';
    file.open("savedata.txt",ios::in|ios::binary);
    if(file.fail())cout<<"File opening failed"<<endl;
    
    //move cursor to end of file
    file.seekg(0L,ios::end);
    //location of cursor is the size of the file
    fSize=file.tellg();
    //move cursor to beginning of file
    file.seekg(0L,ios::beg);
    
    //create temporary "profile" to hold data pulled from file
    Profile Temp;
    for(long cursor=0;cursor<=fSize-sizeof(Temp);cursor+=sizeof(Temp))
    {
        file.read(reinterpret_cast<char*>(&Temp),sizeof(Temp));
        
        if(strcmp(Temp.name,name)==0)
        {
            strcpy(date,Temp.date);
            hscore=Temp.hscore;
            fLctn=cursor;
        }
    }
    cout<<"No profile exists under username "<<name<<endl;
    fLctn=-1;
    
    if(fLctn==-1)
        {
            cout<<"Continue as new user? y for yes, or n to enter another username"<<endl;
            cin.get(option);
            cin.ignore();
            if(option=='n'||option=='N')
            {
                Profile.inputNm();
                Profile.search();
            }
        }
    else 
    {
        cout<<"Welcome, "<<name<<"."<<endl;
        cout<<"Your current high score is "<<hscore<<"."<<endl;
        cout<<"Think you can beat it?"<<endl;
    }
}
Profile::~Profile(){}
#endif /* PROFILE_H */

