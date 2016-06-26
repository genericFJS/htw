#include "person.h"

Person::Person(QString fullName){
    this->fullName = fullName;
}

QString Person::getFullName(){
    return fullName;
}

QString Person::getID(){
    return ID;
}
