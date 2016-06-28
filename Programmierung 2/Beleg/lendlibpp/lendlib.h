#ifndef LENDLIB_H
#define LENDLIB_H

#include "medium.h"
#include "person.h"

class LendLib{
public:
    LendLib();
    void addMediumToList(Medium *newM);
    void addPersonToList(Person *newP);
    void addLendEntry(int mediumID, int personID);
    void removeLendEntry(int mediumID);
    Medium* getMediumEntry(int mediumID);
    Person* getPersonEntry(int personID);
    QMap<int,Medium*> getMList();
    QMap<int,Person*> getPList();

private:
    QMap<int,Medium*> mList;
    QMap<int,Person*> pList;
    QHash<int,int> lendList;    // erste int: Medium-ID, zweite: Person-ID
    int nextID = 0;
//    MainWindow *mainWindow;
};

#endif // LENDLIB_H
