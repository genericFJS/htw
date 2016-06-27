#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
//    this->myLib = new MainWindow(this);
    this->initUI();

//    addMedium(cd, "test1");
//    addMedium(book, "test2");
//    addMedium(cd, "test3");

    addMedium(book,"Die Bibel");
    addMedium(book,"Eragon");
    addMedium(book,"Harry Potter");
    addMedium(cd,"Take That: Best of");
    addMedium(dvd,"Harry Potter");
    addMedium(other,"Programmierung I Skript");

    addPerson("Hans");
    addPerson("Klaus");
    addPerson("Gabi");
    addPerson("Brunhilde");

//    lendlib->addLendEntry(buch1->getID(), person1->getID());
//    lendlib->addLendEntry(buch2->getID(), person2->getID());
//    lendlib->addLendEntry(cd1->getID(), person1->getID());
//    lendlib->addLendEntry(dvd1->getID(), person1->getID());
//    lendlib->addLendEntry(medium1->getID(), person3->getID());

}

void MainWindow::initUI(){
    // Vorlagen löschen:
    ui->allMediaScroll->layout()->removeWidget(ui->mediaEntry1);
    delete ui->mediaEntry1;
    ui->allMediaScroll->layout()->removeWidget(ui->personEntry1);
    delete ui->personEntry1;

    // Medium-Typ Auswahl füllen
    ui->addMediaType->addItem("-");
    ui->addMediaType->addItem("Buch");
    ui->addMediaType->addItem("CD");
    ui->addMediaType->addItem("DVD");

    // Button verknüpfen
    connect(ui->addMediumButton, SIGNAL (released()), this, SLOT (addMediumButton()));
    connect(ui->addPersonButton, SIGNAL (released()), this, SLOT (addPersonButton()));
}

void MainWindow::deleteItemButton(){
   QPushButton *myB = qobject_cast<QPushButton*>(sender());
    ui->allMediaScroll->layout()->removeWidget(myB->parentWidget());
    delete myB->parentWidget();
}

void MainWindow::lendMediumButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
}

void MainWindow::addMediumButton(){
    if(ui->addMediaTitle->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Bitte einen Titel eingeben.");
        msgBox.exec();
    } else {
        MType type;
        QString bType = ui->addMediaType->currentText();
        if (!bType.compare("Buch")){
            type = book;
        } else if (!bType.compare("CD")){
            type = cd;
        } else if (!bType.compare("DVD")){
            type = dvd;
        } else {
            type = other;
        }
        addMedium(type, ui->addMediaTitle->text());
        ui->addMediaTitle->setText("");
    }
}

void MainWindow::addPersonButton(){
    if(ui->addPersonName->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Bitte einen Namen eingeben.");
        msgBox.exec();
    } else {
        addPerson(ui->addPersonName->text());
        ui->addPersonName->setText("");
    }
}

void MainWindow::addMedium(MType mType, QString mName){
    QString mTypeString;
    QString mEntry;
    Medium *medium;
    // Unterscheidung zwischen Medien Typ (erstellen und Typ-String anpassen)
    switch (mType){
    case book:
        mTypeString="Buch";
        medium = new Book(mName);
        break;
    case cd:
        mTypeString="CD";
        medium = new CD(mName);
        break;
    case dvd:
        mTypeString="DVD";
        medium = new DVD(mName);
        break;
    default:
        mTypeString="Other";
        medium = new Medium(mName);
    }
    // Medium in Liste erfassen
    lendlib->addMediumToList(medium);

    mEntry = QString::number(medium->getID());

    // UI-Elemente erstellen
    QWidget *newMedium = new QWidget;
    QHBoxLayout *newMediumLayout = new QHBoxLayout(newMedium);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *type = new QLabel(mTypeString);
    QLabel *title = new QLabel(mName);
    QLabel *lendee = new QLabel("");
    QPushButton *retlendB = new QPushButton("Ausleihen");

    // UI-Eigenschaften
    newMedium->setObjectName(mEntry);
    delB->setObjectName("del"+mEntry);
    delB->setToolTip("Lösche Medium "+mEntry+": "+mName);
    type->setObjectName("type"+mEntry);
    title->setObjectName("title"+mEntry);
    lendee->setObjectName("lend"+mEntry);
    retlendB->setObjectName("retlend"+mEntry);
    retlendB->setToolTip("Leihe Medium "+mEntry+" aus: "+mName);

    newMedium->layout()->setMargin(0);
    delB->setStyleSheet("background: #DEE2CF;");
    delB->setMinimumWidth(60);
    delB->setMaximumWidth(60);
    delB->setMinimumHeight(25);
    delB->setMaximumHeight(25);
    connect(delB, SIGNAL (released()), this, SLOT (deleteItemButton()));
    retlendB->setStyleSheet("background: #DEE2CF;");
    retlendB->setMinimumWidth(80);
    retlendB->setMaximumWidth(80);
    retlendB->setMinimumHeight(25);
    retlendB->setMaximumHeight(25);
    connect(retlendB, SIGNAL (released()), this, SLOT (lendMediumButton()));
    type->setMinimumWidth(60);
    type->setMaximumWidth(60);
    lendee->setMinimumWidth(80);
    lendee->setMaximumWidth(80);

    newMediumLayout->addWidget(delB);
    newMediumLayout->addWidget(type);
    newMediumLayout->addWidget(title);
    newMediumLayout->addWidget(lendee);
    newMediumLayout->addWidget(retlendB);
    qobject_cast<QVBoxLayout*>(ui->allMediaScroll->layout())->insertWidget(-1,newMedium);

    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);
}

void MainWindow::addPerson(QString pName){
    QString pEntry;
    Person *person = new Person(pName);
    // Person in Liste erfassen
    lendlib->addPersonToList(person);

    pEntry = QString::number(person->getID());

    // UI-Elemente erstellen
    QWidget *newMedium = new QWidget;
    QHBoxLayout *newMediumLayout = new QHBoxLayout(newMedium);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *name = new QLabel(pName);
    QWidget *rent = new QWidget;
    QVBoxLayout *rentLayout = new QVBoxLayout(rent);

    // UI-Eigenschaften
    newMedium->setObjectName(pEntry);
    delB->setObjectName("del"+pEntry);
    delB->setToolTip("Lösche Person "+pEntry+": "+pName);
    name->setObjectName("name"+pEntry);
    rent->setObjectName("rent"+pEntry);

    newMedium->layout()->setMargin(0);
    rent->layout()->setMargin(0);
    delB->setStyleSheet("background: #DEE2CF;");
    delB->setMinimumWidth(60);
    delB->setMaximumWidth(60);
    delB->setMinimumHeight(25);
    delB->setMaximumHeight(25);
    connect(delB, SIGNAL (released()), this, SLOT (deleteItemButton()));
    rent->setMaximumWidth(120);

    newMediumLayout->addWidget(delB);
    newMediumLayout->addWidget(name);
    newMediumLayout->addWidget(rent);
    qobject_cast<QVBoxLayout*>(ui->allPersonsScroll->layout())->insertWidget(-1,newMedium);

    ui->allPersonsScroll->layout()->removeItem(ui->personSpacer);
    ui->allPersonsScroll->layout()->addItem(ui->personSpacer);
}


MainWindow::~MainWindow(){
    delete ui;
}

