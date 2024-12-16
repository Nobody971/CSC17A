#ifndef PROFILE_H
#define PROFILE_H

#include <cstring>
using namespace std;

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
        void top5();//finds and displays top 5 scores
        void save(Profile&);//writes specified profile to file
        ~Profile(){}//destructor
};

#endif /* PROFILE_H */

