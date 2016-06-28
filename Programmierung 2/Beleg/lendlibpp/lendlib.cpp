#include "lendlib.h"

LendLib::LendLib(){
//    this->mainWindow = mainWindow;
}

void LendLib::addMediumToList(Medium *newM){
    newM->setID(this->nextID);
    nextID++;
    this->mList.insert(newM->getID(),newM);
}

void LendLib::addPersonToList(Person *newP){
    newP->setID(this->nextID);
    nextID++;
    this->pList.insert(newP->getID(),newP);
}

void LendLib::addLendEntry(int mediumID, int personID){
    this->lendList.insert(mediumID, personID);
}

void LendLib::removeLendEntry(int mediumID){
    this->lendList.remove(mediumID);
}

Medium* LendLib::getMediumEntry(int mediumID){
    return this->mList.value(mediumID);
}

Person* LendLib::getPersonEntry(int personID){
    return this->pList.value(personID);
}

QMap<int, Medium *> LendLib::getMList(){
    return mList;
}

QMap<int, Person *> LendLib::getPList(){
    return pList;
}
