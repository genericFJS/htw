// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QSizePolicy>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <iterator>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "book.h"
#include "lendlib.h"
#include "cd.h"
#include "dvd.h"
#include "mediumtype.h"
#include "other.h"
#include "person.h"
using namespace std;

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class ist für das UI und die Interaktion mit der Datenbank verantwortlich
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void deleteMediumButton();
    void deletePersonButton();
    void retlendMediumButton();
    void addMediumButton();
    void addPersonButton();
    void changeMediaInput();

private:
    Ui::MainWindow *ui;
    LendLib *lendlib = new LendLib();
    bool readErr = false;
    bool otherErr = false;
    QString errString;
    void fillDemoData(bool more=false);
    void initUI();
    void checkError();
    void fillLibFromFile();
    void saveLibToFile();
    int addMedium(MType mType, QString mName, QString detail, int mID=-1);
    int addPerson(QString pName, int pID=-1);
    void lendMedium(int mediumID, int personID);
    void returnMedium(int mediumID);
    void deleteMedium(int mediumID);
    void deletePerson(int personID);
    int getInsertPosition(QString entry, bool isMedium = true);
};

#endif // MAINWINDOW_H
