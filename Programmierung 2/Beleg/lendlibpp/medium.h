// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef MEDIUM_H
#define MEDIUM_H

#include <QApplication>
#include "mediumtype.h"

/**
 * @brief The Medium class beschreibt die Grundeigenschaften aller Medien
 */
class Medium{
public:
    Medium(QString title, MType type = other);
    QString getTitle();
    int getID();
    void setID(int ID);
    MType getType();

private:
    QString title;
    int ID;
    MType type = other;

};

#endif // MEDIUM_H
