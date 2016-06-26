#include "medium.h"

Medium::Medium(QString title){
    this->title = title;
}

QString Medium::getTitle(){
    return title;
}

QString Medium::getID(){
    return ID;
}
