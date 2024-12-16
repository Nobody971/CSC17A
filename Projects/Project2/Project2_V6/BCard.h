#ifndef BCARD_H
#define BCARD_H

class BCard
{
protected:
    const short SIZE=9;
public:
    BCard(){};
    short getSize(BCard &C){return C.SIZE;}
    virtual char *getFace()=0;
    virtual char *getSuit()=0;
    virtual~BCard(){};
};

#endif /* BCARD_H */

