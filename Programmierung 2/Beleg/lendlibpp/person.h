#ifndef PERSON_H
#define PERSON_H


class Person{
public:
    Person(QString fullName);
    QString getFullName();
    QString getID();
private:
    QString fullName;
    int ID;
};

#endif // PERSON_H
