#include "medium.h"

Medium::Medium(QString title){
    this->title = title;
}

QString Medium::getTitle(){
    return title;
}

int Medium::getID(){
    return ID;
}

void Medium::setID(int ID){
    this->ID = ID;
}
