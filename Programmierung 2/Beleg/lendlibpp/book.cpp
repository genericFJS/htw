#include "book.h"

Book::Book(QString title) : Medium(title){
    this->setType(book);
}
