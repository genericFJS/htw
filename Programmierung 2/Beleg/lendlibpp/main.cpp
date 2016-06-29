// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "mainwindow.h"
#include <QApplication>

/**
 * @brief main hier geht's los
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
