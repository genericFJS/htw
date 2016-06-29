#include "cd.h"

CD::CD(QString title) : Medium(title){
    this->setType(cd);
}
