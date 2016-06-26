#ifndef LENDLIB_H
#define LENDLIB_H

#include "medium.h"
#include "person.h"

class lendlib{
public:
    lendlib();
private:
    QList<Medium> mList;
    QList<Person> pList;
    QHash<Medium,Person> lendList;
};

#endif // LENDLIB_H
