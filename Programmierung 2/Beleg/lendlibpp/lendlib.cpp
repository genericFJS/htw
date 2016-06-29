#include "lendlib.h"

LendLib::LendLib(){
//    this->mainWindow = mainWindow;
}

bool LendLib::addMediumToList(Medium *newM){
    while (mList.contains(nextID) || pList.contains(nextID))
        nextID++;
    newM->setID(this->nextID);
    nextID++;
    this->mList.insert(newM->getID(),newM);
    return true;
}

bool LendLib::addPersonToList(Person *newP){
    while (mList.contains(nextID) || pList.contains(nextID))
        nextID++;
    newP->setID(this->nextID);
    nextID++;
    this->pList.insert(newP->getID(),newP);
    return true;
}

bool LendLib::addMediumToList(Medium *newM, int newID){
    if (mList.contains(newID) || pList.contains(newID))
        return false;
    newM->setID(newID);
    if (newID > nextID){
        nextID = newID+1;
    }
    this->mList.insert(newM->getID(),newM);
    return true;
}

bool LendLib::addPersonToList(Person *newP, int newID){
    if (mList.contains(newID) || pList.contains(newID))
        return false;
    newP->setID(newID);
    if (newID > nextID){
        nextID = newID+1;
    }
    this->pList.insert(newP->getID(),newP);
    return true;
}

void LendLib::addLendEntry(int mediumID, int personID){
    this->lendList.insert(mediumID, personID);
}

void LendLib::removeLendEntry(int mediumID){
    this->lendList.remove(mediumID);
}

void LendLib::deleteMedium(int mediumID){
    this->mList.remove(mediumID);
}

void LendLib::deletePerson(int personID){
    this->pList.remove(personID);
}

bool LendLib::isMediumEntry(int mediumID){
    if (mList.contains(mediumID)){
        return true;
    }
    return false;
}

bool LendLib::isPersonEntry(int personID){
    if (pList.contains(personID)){
        return true;
    }
    return false;
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

QHash<int, int> LendLib::getLendList(){
    return lendList;
}

QList<int> LendLib::getLendMedia(int personID){
    QList<int> mList;
    int i = 1;
    for (auto m: lendList.keys()){
        i++;
        if (lendList.value(m) == personID){
            mList.append(m);
        }
    }
    return mList;
}
