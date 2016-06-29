// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "cd.h"

/**
 * @brief CD::CD Konstruktor ruft Konstruktor von Medium mit dem Typ DVD auf
 * @param title Titel der CD
 */
CD::CD(QString title) : Medium(title, cd){
}

/**
 * @brief CD::setInterpret setzt Namen des Interprets der CD
 * @param interpret Name des Interprets
 */
void CD::setInterpret(QString interpret){
    this->interpret = interpret;
}

/**
 * @brief CD::getInterpret ruft Namen des Interprets der CD ab
 * @return Name des Interprets
 */
QString CD::getInterpret(){
    return this->interpret;
}
