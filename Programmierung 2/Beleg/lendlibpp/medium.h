#ifndef MEDIUM_H
#define MEDIUM_H

class Medium{
public:
    Medium(QString title);
    QString getTitle();
    QString getID();

private:
    QString title;
    int ID;

};

#endif // MEDIUM_H
