#ifndef CD_H
#define CD_H
#include "medium.h"

class CD : public Medium{
public:
    CD(QString title);
private:
    QString interpret;
};

#endif // CD_H
