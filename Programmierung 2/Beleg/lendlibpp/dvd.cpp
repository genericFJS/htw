#include "dvd.h"

DVD::DVD(QString title) : Medium(title){
    this->setType(dvd);
}
