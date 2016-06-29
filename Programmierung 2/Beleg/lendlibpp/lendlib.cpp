// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "lendlib.h"

/**
 * @brief LendLib::LendLib Konstruktor
 */
LendLib::LendLib(){
}

/**
 * @brief LendLib::addMediumToList fügt Medium zu Datenbank hinzu
 * @param newM neues Medium
 * @return true, wenn Medium erfolgreich eingetragen wurde
 */
bool LendLib::addMediumToList(Medium *newM){
    while (mList.contains(nextID) || pList.contains(nextID))
        nextID++;
    newM->setID(this->nextID);
    nextID++;
    this->mList.insert(newM->getID(),newM);
    return true;
}

/**
 * @brief LendLib::addPersonToList fügt Person zu Datenbank hinzu
 * @param newP neue Person
 * @return true, wenn Person erfolgreich eingetragen wurde
 */
bool LendLib::addPersonToList(Person *newP){
    while (mList.contains(nextID) || pList.contains(nextID))
        nextID++;
    newP->setID(this->nextID);
    nextID++;
    this->pList.insert(newP->getID(),newP);
    return true;
}

/**
 * @brief LendLib::addMediumToList fügt Medium zu Datenbank hinzu unter Vorgabe der ID
 * @param newM neues Medium
 * @param newID ID des neuen Mediums
 * @return true, wenn Medium erfolgreich eingetragen wurde
 */
bool LendLib::addMediumToList(Medium *newM, int newID){
    /// kann nicht eingetragen werden, wenn ID bereits in Datenbank vorhanden ist
    if (mList.contains(newID) || pList.contains(newID))
        return false;
    newM->setID(newID);
    if (newID > nextID){
        nextID = newID+1;
    }
    this->mList.insert(newM->getID(),newM);
    return true;
}

/**
 * @brief LendLib::addPersonToList fügt Person zu Datenbank hinzu unter Vorgabe der ID
 * @param newP neue Person
 * @param newID ID der neuen Person
 * @return true, wenn Person erfolgreich eingetragen wurde
 */
bool LendLib::addPersonToList(Person *newP, int newID){
    /// kann nicht eingetragen werden, wenn ID bereits in Datenbank vorhanden ist
    if (mList.contains(newID) || pList.contains(newID))
        return false;
    newP->setID(newID);
    if (newID > nextID){
        nextID = newID+1;
    }
    this->pList.insert(newP->getID(),newP);
    return true;
}

/**
 * @brief LendLib::addLendEntry fügt neue Ausleih-Relation zu Datenbank hinzu
 * @param mediumID ausgeliehenes Medium
 * @param personID ausleihende Person
 */
void LendLib::addLendEntry(int mediumID, int personID){
    this->lendList.insert(mediumID, personID);
}

/**
 * @brief LendLib::removeLendEntry entfernt Ausleih-Relation aus Datenbank
 * @param mediumID zurückgegebenes Medium
 */
void LendLib::removeLendEntry(int mediumID){
    this->lendList.remove(mediumID);
}

/**
 * @brief LendLib::deleteMedium löscht Medium
 * @param mediumID ID des zu löschenden Mediums
 */
void LendLib::deleteMedium(int mediumID){
    this->mList.remove(mediumID);
}

/**
 * @brief LendLib::deletePerson löscht Person
 * @param personID ID der zu löschenden Person
 */
void LendLib::deletePerson(int personID){
    this->pList.remove(personID);
}

/**
 * @brief LendLib::isMediumEntry überprüft, ob ID einer Medium-ID entspricht
 * @param mediumID zu prüfende ID
 * @return true, wenn ID einem Medium entspricht
 */
bool LendLib::isMediumEntry(int mediumID){
    if (mList.contains(mediumID)){
        return true;
    }
    return false;
}

/**
 * @brief LendLib::isPersonEntry überprüft, ob ID einer Personen-ID entspricht
 * @param personID zu prüfende ID
 * @return true, wenn ID einer Person entspricht
 */
bool LendLib::isPersonEntry(int personID){
    if (pList.contains(personID)){
        return true;
    }
    return false;
}

/**
 * @brief LendLib::getMediumEntry ruft Medium ab
 * @param mediumID ID des Mediums
 * @return gefundese Medium
 */
Medium* LendLib::getMediumEntry(int mediumID){
    return this->mList.value(mediumID);
}

/**
 * @brief LendLib::getPersonEntry ruft Person ab
 * @param personID ID der Person
 * @return gefundene Person
 */
Person* LendLib::getPersonEntry(int personID){
    return this->pList.value(personID);
}

/**
 * @brief LendLib::getMList ruft gesamte Medienliste ab
 * @return Medienliste
 */
QMap<int, Medium *> LendLib::getMList(){
    return mList;
}

/**
 * @brief LendLib::getPList ruft gesamte Personenliste ab
 * @return Personenliste
 */
QMap<int, Person *> LendLib::getPList(){
    return pList;
}

/**
 * @brief LendLib::getLendList ruft gesamte Liste der Ausleih-Relationen ab
 * @return Ausleih-Relationen Liste
 */
QHash<int, int> LendLib::getLendList(){
    return lendList;
}

/**
 * @brief LendLib::getLendMedia ruft alle Medien ab, die eine Person geliehen hat
 * @param personID ID der Person, deren ausgeliehene Medien gesucht ist
 * @return Liste von Medien-IDs, die von Person ausgeliehen sind
 */
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
