// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "person.h"

/**
 * @brief Person::Person Konstruktor
 * @param fullName Name der Person
 */
Person::Person(QString fullName){
    this->fullName = fullName;
}

/**
 * @brief Person::getFullName gibt Namen der Person aus
 * @return Name der Person
 */
QString Person::getFullName(){
    return fullName;
}

/**
 * @brief Person::getID gibt ID der Person aus
 * @return ID der Person
 */
int Person::getID(){
    return ID;
}

/**
 * @brief Person::setID setzt ID der Person
 * @param ID auf diese ID neu setzen
 */
void Person::setID(int ID){
    this->ID = ID;
}
