// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef DVD_H
#define DVD_H
#include "medium.h"

/**
 * @brief The DVD class ist ein Medium mit besonderen Eigenschaften (Regisseur)
 */
class DVD : public Medium{
public:
    DVD(QString title);
    void setDirector(QString director);
    QString getDirector();
private:
    QString director = "";
};

#endif // DVD_H
