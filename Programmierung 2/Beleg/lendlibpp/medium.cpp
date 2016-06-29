// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "medium.h"

/**
 * @brief Medium::Medium Konstruktor
 * @param title Titel des Mediums
 * @param type Typ des Mediums (wenn nicht angegeben, dann "other")
 */
Medium::Medium(QString title, MType type){
    this->title = title;
    this->type = type;
}

/**
 * @brief Medium::getTitle gibt Titel des Mediums aus
 * @return Titel des Mediums
 */
QString Medium::getTitle(){
    return title;
}

/**
 * @brief Medium::getID gibt ID des Titels aus
 * @return ID des Titels
 */
int Medium::getID(){
    return ID;
}

/**
 * @brief Medium::setID setzt ID des Titels
 * @param ID auf diese ID neu setzen
 */
void Medium::setID(int ID){
    this->ID = ID;
}

/**
 * @brief Medium::getType gibt Typ des Mediums aus
 * @return Typ des Mediums
 */
MType Medium::getType(){
    return type;
}
