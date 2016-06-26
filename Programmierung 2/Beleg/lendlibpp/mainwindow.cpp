#include <iostream>
using namespace std;
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    int j=0;
    while(j<3){
        QWidget *newMedium = new QWidget;
        newMedium->setObjectName("med"+QString::number(j));
        QHBoxLayout *newMediumLayout = new QHBoxLayout(newMedium);
        newMedium->layout()->setMargin(0);
        QString delName = "Löschen"+QString::number(j);
        QPushButton *delB = new QPushButton("Löschen");
        delB->setObjectName(delName);
        QLabel *type = new QLabel("Typ");
        QLabel *title = new QLabel("Titel"+QString::number(j));
        QLabel *lendee = new QLabel("Ausgeliehen an");
        QPushButton *retlendB = new QPushButton("Ausleihen");

        delB->setStyleSheet("background: #DEE2CF;");
        connect(delB, SIGNAL (released()), this, SLOT (deleteItemButton()));
        retlendB->setStyleSheet("background: #DEE2CF;");
        delB->setMinimumWidth(60);
        delB->setMaximumWidth(60);
        delB->setMinimumHeight(25);
        delB->setMaximumHeight(25);
        retlendB->setMinimumWidth(80);
        retlendB->setMaximumWidth(80);
        retlendB->setMinimumHeight(25);
        retlendB->setMaximumHeight(25);
        type->setMinimumWidth(60);
        type->setMaximumWidth(60);
        lendee->setMinimumWidth(80);
        lendee->setMaximumWidth(80);

        newMediumLayout->addWidget(delB);
        newMediumLayout->addWidget(type);
        newMediumLayout->addWidget(title);
        newMediumLayout->addWidget(lendee);
        newMediumLayout->addWidget(retlendB);
        ui->allMediaScroll->layout()->addWidget(newMedium);
        j++;
    }

//    delete ui->mediaSpacer;
    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);

    connect(ui->mediaDel1, SIGNAL (released()), this, SLOT (deleteItemButton()));
}

void MainWindow::deleteItemButton(){
   QPushButton *myB = qobject_cast<QPushButton*>(sender());

//    ui->debug->setText(" Sender:"+myB->objectName()+" Parent:"+myB->parentWidget()->objectName());
    cerr<<"Deleting: " << (myB->parentWidget()->objectName()).toUtf8().constData() << " | " << myB->parentWidget()->parentWidget()->children().length() << endl;

    ui->allMediaScroll->layout()->removeWidget(myB->parentWidget());
    delete myB->parentWidget();
}

void MainWindow::addMediumUI(){
    // UI-Elemente erstellen
    int j = 1;
    QWidget *newMedium = new QWidget;
    QHBoxLayout *newMediumLayout = new QHBoxLayout(newMedium);
    QString delName = "Löschen"+QString::number(j);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *type = new QLabel("Typ");
    QLabel *title = new QLabel("Titel"+QString::number(j));
    QLabel *lendee = new QLabel("Ausgeliehen an");
    QPushButton *retlendB = new QPushButton("Ausleihen");

    // UI-Eigenschaften
    newMedium->setObjectName("med"+QString::number(j));
    newMedium->layout()->setMargin(0);
    delB->setObjectName(delName);

    delB->setStyleSheet("background: #DEE2CF;");
    connect(delB, SIGNAL (released()), this, SLOT (deleteItemButton()));
    retlendB->setStyleSheet("background: #DEE2CF;");
    delB->setMinimumWidth(60);
    delB->setMaximumWidth(60);
    delB->setMinimumHeight(25);
    delB->setMaximumHeight(25);
    retlendB->setMinimumWidth(80);
    retlendB->setMaximumWidth(80);
    retlendB->setMinimumHeight(25);
    retlendB->setMaximumHeight(25);
    type->setMinimumWidth(60);
    type->setMaximumWidth(60);
    lendee->setMinimumWidth(80);
    lendee->setMaximumWidth(80);

    newMediumLayout->addWidget(delB);
    newMediumLayout->addWidget(type);
    newMediumLayout->addWidget(title);
    newMediumLayout->addWidget(lendee);
    newMediumLayout->addWidget(retlendB);
    ui->allMediaScroll->layout()->addWidget(newMedium);


    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);
}

MainWindow::~MainWindow(){
    delete ui;
}

