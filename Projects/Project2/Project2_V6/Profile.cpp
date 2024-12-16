#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

#include "Profile.h"

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
void Profile::top5()
{   
    ifstream file;
    vector<short> scores;
    long fSize;
    long cursor;
    file.open("savedata.txt",ios::in|ios::binary);
    if(file.fail())cout<<"File opening failed"<<endl;
    
    //move cursor to end of file
    file.seekg(0L,ios::end);
    //location of cursor is the size of the file
    fSize=file.tellg();
    //move cursor to beginning of file
    file.seekg(0L,ios::beg);
    
    Profile Temp;
    for(long cursor=0;cursor<=fSize-sizeof(Temp);cursor+=sizeof(Temp))
    {
        file.read(reinterpret_cast<char*>(&Temp),sizeof(Temp));
        scores.push_back(Temp.hscore);
    }
    sort(scores.begin(),scores.end());
    
    cout<<"--------------"<<endl;
    cout<<"| Top Scores |"<<endl;
    cout<<"--------------"<<endl;
    for(short i=scores.size()-1;i>=0;i--)
    {
        cout<<"|     "<<left<<setw(2)<<scores[i]<<"     |"<<endl;
        cout<<"-------------"<<endl;
    }
    cout<<right;
    scores.clear();
    file.close();
}
void Profile::save(Profile &User)
{
    cout<<"Input today's date xx/xx/xxxx"<<endl;
    cin.ignore();
    cin.getline(date,SIZE);
    if(fLctn==-2)
    {
        throw 0;
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