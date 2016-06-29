#ifndef LENDLIB_H
#define LENDLIB_H

#include "medium.h"
#include "person.h"
#include <iostream>
using namespace std;

class LendLib{
public:
    LendLib();
    bool addMediumToList(Medium *newM);
    bool addPersonToList(Person *newP);
    bool addMediumToList(Medium *newM, int newID);
    bool addPersonToList(Person *newP, int newID);
    void addLendEntry(int mediumID, int personID);
    void removeLendEntry(int mediumID);
    void deleteMedium(int mediumID);
    void deletePerson(int personID);
    bool isMediumEntry(int mediumID);
    bool isPersonEntry(int personID);
    Medium* getMediumEntry(int mediumID);
    Person* getPersonEntry(int personID);
    QMap<int,Medium*> getMList();
    QMap<int,Person*> getPList();
    QHash<int,int> getLendList();
    QList<int> getLendMedia(int personID);

private:
    QMap<int,Medium*> mList;
    QMap<int,Person*> pList;
    QHash<int,int> lendList;    // erste int: Medium-ID, zweite: Person-ID
    int nextID = 0;
//    MainWindow *mainWindow;
};

#endif // LENDLIB_H
