#ifndef DVD_H
#define DVD_H
#include "medium.h"

class DVD : public Medium{
public:
    DVD(QString title);
private:
    QString director;
};

#endif // DVD_H
