#ifndef PERSON_H
#define PERSON_H

#include <QApplication>

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
