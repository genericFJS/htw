// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef PERSON_H
#define PERSON_H

#include <QApplication>

/**
 * @brief The Person class beschreibt die Eigenschaften einer Person
 */
class Person{
public:
    Person(QString fullName);
    QString getFullName();
    int getID();
    void setID(int ID);
private:
    QString fullName;
    int ID;
};

#endif // PERSON_H
