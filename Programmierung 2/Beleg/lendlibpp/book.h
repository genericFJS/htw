// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef BOOK_H
#define BOOK_H
#include "medium.h"

/**
 * @brief The Book class ist ein Medium mit besonderen Eigenschaften (Autor)
 */
class Book : public Medium{
public:
    Book(QString title);
    void setAuthor(QString author);
    QString getAuthor();
private:
    QString author = "";
};

#endif // BOOK_H
