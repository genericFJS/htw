#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
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

private:
    Ui::MainWindow *ui;
    LendLib *lendlib = new LendLib();
    void initUI();
    void addMedium(MType mType, QString mName);
    void addPerson(QString pName);
    void lendMedium(int mediumID, int personID);
    void returnMedium(int mediumID);
};

#endif // MAINWINDOW_H
