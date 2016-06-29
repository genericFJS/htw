// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "dvd.h"

/**
 * @brief DVD::DVD Konstruktor ruft Konstruktor von Medium mit dem Typ DVD auf
 * @param title Titel der DVD
 */
DVD::DVD(QString title) : Medium(title, dvd){
}

/**
 * @brief DVD::setDirector setzt Namen des Regisseurs vom Film
 * @param director Name des Regisseurs
 */
void DVD::setDirector(QString director){
    this->director = director;
}

/**
 * @brief DVD::getDirector ruft Namen des Regisseurs vom Film ab
 * @return Name des Regisseurs
 */
QString DVD::getDirector(){
    return this->director;
}
