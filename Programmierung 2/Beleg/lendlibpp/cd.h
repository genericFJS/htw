// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef CD_H
#define CD_H
#include "medium.h"

/**
 * @brief The CD class ist ein Medium mit besonderen Eigenschaften (Interpret)
 */
class CD : public Medium{
public:
    CD(QString title);
    void setInterpret(QString interpret);
    QString getInterpret();
private:
    QString interpret = "";
};

#endif // CD_H
