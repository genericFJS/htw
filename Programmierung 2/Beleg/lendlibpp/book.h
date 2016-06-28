#ifndef BOOK_H
#define BOOK_H
#include "medium.h"

class Book : public Medium{
public:
    Book(QString title);
private:
    QString author;
};

#endif // BOOK_H
