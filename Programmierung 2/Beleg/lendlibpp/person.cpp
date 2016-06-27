#include "person.h"

Person::Person(QString fullName){
    this->fullName = fullName;
}

QString Person::getFullName(){
    return fullName;
}

int Person::getID(){
    return ID;
}

void Person::setID(int ID){
    this->ID = ID;
}
