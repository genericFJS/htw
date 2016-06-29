#ifndef MEDIUM_H
#define MEDIUM_H

#include <QApplication>
#include "mediumtype.h"

class Medium{
public:
    Medium(QString title);
    QString getTitle();
    int getID();
    void setID(int ID);
    MType getType();
    void setType(MType type);

private:
    QString title;
    int ID;
    MType type = other;

};

#endif // MEDIUM_H
