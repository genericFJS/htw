#ifndef MEDIUM_H
#define MEDIUM_H

#include <QApplication>

class Medium{
public:
    Medium(QString title);
    QString getTitle();
    int getID();
    void setID(int ID);

private:
    QString title;
    int ID;

};

#endif // MEDIUM_H
