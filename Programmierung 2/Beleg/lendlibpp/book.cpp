// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "book.h"

/**
 * @brief Book::Book Konstruktor ruft Konstruktor von Medium mit dem Typ Buch auf
 * @param title Titel des Buchs
 */
Book::Book(QString title) : Medium(title, book){
}

/**
 * @brief Book::setAuthor setzt Name des Autors des Buches
 * @param author Name des Autors
 */
void Book::setAuthor(QString author){
    this->author = author;
}

/**
 * @brief Book::getAuthor ruft Name des Autors des Buches ab
 * @return Name des Autors
 */
QString Book::getAuthor(){
    return this->author;
}
