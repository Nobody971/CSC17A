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
#include <limits>

class Profile
{
    private:
        char name[11];
        char date[11];
        const short SIZE=11;
        short hscore;
        long fLctn;//location of profile in file
        void search();//searches file for entered username;
    public:
        Profile();//constructor
        short getSize(){return SIZE;}
        short getScr(){return hscore;}//returns hscore
        long getLctn(){return fLctn;}//returns location of profile in file
        void setScr(short s){hscore=s;}//changes hscore to specified value
        void inputNm();//reads user input for name
        void copyNm(char n[]){strcpy(n,name);}//copies name to specified char array
        void save(Profile&);//writes specified profile to file
        ~Profile(){}//destructor
};

Profile::Profile()
{
    strcpy(name," ");
    strcpy(date," ");
    hscore=0;
    fLctn=-2;
}
void Profile::inputNm()
{
    char option='x';
    do
    {
        cout<<"Please input your username. Max 10 characters."<<endl;
        cin.getline(name,SIZE);
        cout<<name<<", is this correct? y for yes and n for no"<<endl;
                cin.get(option);
                cin.ignore();
    }while(option!='y'&&option!='Y');
    search();
}
void Profile::search()
{
    ifstream file;
    long fSize;
    long cursor;
    char option='x';
    file.open("savedata.txt",ios::in|ios::binary);
    if(file.fail())cout<<"File opening failed"<<endl;
    
    //move cursor to end of file
    file.seekg(0L,ios::end);
    //location of cursor is the size of the file
    fSize=file.tellg();
    //give fLctn invalid value if file size is zero
    if(fSize==0){cout<<"No saved data available. Continuing as new user."<<endl;fLctn=-1;return;}
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
    if(fLctn==-2)
    {
        cout<<"No profile exists under username "<<name<<endl;
        cout<<"Continue as new user? y for yes, or n to enter another username"<<endl;
        cin.get(option);
        cin.ignore();
        if(option=='n'||option=='N')
        {
            inputNm();
        }
        else
        {
            fLctn=-1;
            cout<<"Welcome, "<<name<<"!"<<endl;
        }
    }
    else 
    {
        cout<<"Welcome, "<<name<<"."<<endl;
        cout<<"Your current high score is "<<hscore<<"."<<endl;
        cout<<"Think you can beat it?"<<endl;
    }
    file.close();
}
void Profile::save(Profile &User)
{
    cout<<"Input today's date xx/xx/xxxx"<<endl;
    cin.ignore();
    cin.getline(date,SIZE);
    if(fLctn==-2)
    {
        cout<<"Error. Cannot save to file."<<endl;
    }
    else if(fLctn==-1)
    {
        ofstream file;
        file.open("savedata.txt",ios::app|ios::binary);
        file.write(reinterpret_cast<char*>(&User),sizeof(User));
        file.close();
    }
    else
    {
        fstream file;
        file.open("savedata.txt",ios::in|ios::out|ios::binary);
        file.seekp(fLctn,ios::beg);
        file.write(reinterpret_cast<char*>(&User),sizeof(User));
        file.close();
    }
    cout<<"Profile saved to file"<<endl;
}
#endif /* PROFILE_H */

