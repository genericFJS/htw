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

MType Medium::getType(){
    return type;
}

void Medium::setType(MType type){
    this->type = type;
}
