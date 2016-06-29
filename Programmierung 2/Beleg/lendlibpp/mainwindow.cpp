#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->initUI();
    this->fillLibFromFile();
    checkError();

    fillDemoData();
//    fillDemoData(true);

}

void MainWindow::fillDemoData(bool more){
    QString addNo = "";
    if (more){
        qsrand( QDateTime::currentDateTime().toTime_t() );
        addNo = " ("+QString::number(qrand()%100)+")";
    }

    if (more || (lendlib->getMList().empty() && lendlib->getPList().empty())){
        int m1 = addMedium(book,"Die Bibel"+addNo);
        int m2 = addMedium(book,"Eragon"+addNo);
        addMedium(book,"Harry Potter"+addNo);
        int m4 = addMedium(cd,"Take That: Best of"+addNo);
        int m5 = addMedium(dvd,"Harry Potter"+addNo);
        int m6 =  addMedium(other,"Programmierung I Skript"+addNo);

        int p1 = addPerson("Hans"+addNo);
        int p2 = addPerson("Klaus"+addNo);
        int p3 = addPerson("Gabi"+addNo);
        addPerson("Brunhilde"+addNo);

        lendMedium(m1, p1);
        lendMedium(m2, p2);
        lendMedium(m4, p1);
        lendMedium(m5, p1);
        lendMedium(m6, p3);
    }
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

void MainWindow::checkError(){
    QMessageBox msgBox;
    if (readErr){
        msgBox.setText("Es gab einen Fehler beim einlesen der Datenbank:\n"+errString+"\nBitte löschen Sie die .csv Dateien und erstellen Sie eine neue Datei.");
        msgBox.exec();
        exit(0);
    } else if (otherErr) {
        msgBox.setText("Es gab einen Fehler:\n"+errString);
        msgBox.exec();
        exit(0);
    }
}

void MainWindow::fillLibFromFile(){
    QFile lendFile("lendlibLend.csv");
    QFile mFile("lendlibMedia.csv");
    QFile pFile("lendlibPerson.csv");
    QList<int> idList;
    if (mFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        mFile.readLine();
        while (!mFile.atEnd()) {
            QByteArray line = mFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            if (lineElements.length() == 3){
                int newID = lineElements[0].toInt();
                if(idList.contains(newID)){
                    errString = "Fehler beim Lesen der Datei 'lendlibMedia.csv' in Zeile "+ QString::number(lineNumber)+" (ID bereits vorhanden).";
                    readErr = true;
                    return;
                }
                idList.append(newID);
                MType mType;
                switch (lineElements[1].toInt()){
                case 0:
                    mType = book;
                    break;
                case 1:
                    mType = cd;
                    break;
                case 2:
                    mType = dvd;
                    break;
                default:
                    mType = other;
                }
                addMedium(mType,QString::fromStdString(lineElements[2].toStdString()),newID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibMedia.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 3 Elemente).";
                readErr = true;
                return;
            }
        }
    }
    if (pFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        pFile.readLine();
        while (!pFile.atEnd()) {
            QByteArray line = pFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            if (lineElements.length() == 2){
                int newID = lineElements[0].toInt();
                if(idList.contains(newID)){
                    errString = "Fehler beim Lesen der Datei 'lendlibPerson.csv' in Zeile "+ QString::number(lineNumber)+" (ID bereits vorhanden).";
                    readErr = true;
                    return;
                }
                idList.append(newID);
                addPerson(QString::fromStdString(lineElements[1].toStdString()),newID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibPerson.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 2 Elemente).";
                readErr = true;
                return;
            }
        }
    }
    if (lendFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        lendFile.readLine();
        while (!lendFile.atEnd()) {
            QByteArray line = lendFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            if (lineElements.length() == 2){
                int mediumID = lineElements[0].toInt();
                int personID = lineElements[1].toInt();
                if(!lendlib->isMediumEntry(mediumID)){
                    errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (ID ist kein Medium).";
                    readErr = true;
                    return;
                }
                if(!lendlib->isPersonEntry(personID)){
                    cerr << lineElements[0].toStdString() << " "<< mediumID << "\n";
                    cerr << lineElements[1].toStdString() << " "<< personID << "\n";
                    errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (ID ist keine Person).";
                    readErr = true;
                    return;
                }
                lendMedium(mediumID, personID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 2 Elemente).";
                readErr = true;
                return;
            }
        }
    }
}

void MainWindow::saveLibToFile(){
    QFile lendFile("lendlibLend.csv");
    QFile mFile("lendlibMedia.csv");
    QFile pFile("lendlibPerson.csv");
    if (lendFile.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream stream(&lendFile);
        QHash<int,int> lendList = lendlib->getLendList();
        QHash<int,int>::iterator i;
        stream << "Medium \t Ausgeliehen an\n";
        for(i = lendList.begin(); i != lendList.end(); ++i){
            stream << i.key() << "\t" << i.value() << "\n";
        }
        lendFile.close();
    }
    if (mFile.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream stream(&mFile);
        QMap<int,Medium*> mList = lendlib->getMList();
        stream << "ID \t Typ \t Titel\n";
        for(auto m: mList.keys()){
            stream << mList.value(m)->getID() << "\t" << mList.value(m)->getType() << "\t" << mList.value(m)->getTitle() << "\n";
        }
        mFile.close();
    }
    if (pFile.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream stream(&pFile);
        QMap<int,Person*> pList = lendlib->getPList();
        stream << "ID \t Name\n";
        for(auto p: pList.keys()){
            stream << pList.value(p)->getID()<< "\t" << pList.value(p)->getFullName() << "\n";
        }
        pFile.close();
    }
}

void MainWindow::retlendMediumButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    int mediumID = sender()->parent()->objectName().toInt();
    if(!myB->text().compare("Ausleihen")){
        QStringList persons;
        QMap<int,Person*> allP = lendlib->getPList();
        for (auto p: allP.keys()){
            persons.append(allP.value(p)->getFullName()+" | ID: "+QString::number(allP.value(p)->getID()));
        }
        bool ok;
        QString person = QInputDialog::getItem(this, "Ausleihen", "Ausleihen an:", persons, 0, false, &ok);
        if (ok && !person.isEmpty()){
            int personID = (person.split(" ID: ").last()).toInt();
            lendMedium(mediumID, personID);
        }
    } else {
        returnMedium(mediumID);
    }
}

void MainWindow::deleteMediumButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    deleteMedium(myB->parentWidget()->objectName().toInt());
}

void MainWindow::deletePersonButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    deletePerson(myB->parentWidget()->objectName().toInt());
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

int MainWindow::addMedium(MType mType, QString mName, int mID){
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
    if (mID == -1){
        lendlib->addMediumToList(medium);
    } else {
        if (!lendlib->addMediumToList(medium, mID)){
            otherErr = true;
            errString = "Medium konnte nicht mit vorgegebener ID eingegeben werden.";
            checkError();
        }
    }

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
    lendee->setObjectName("lendee"+mEntry);
    retlendB->setObjectName("retlend"+mEntry);
    retlendB->setToolTip("Leihe Medium "+mEntry+" aus: "+mName);

    newMedium->layout()->setMargin(0);
    newMedium->setStyleSheet("border-bottom: 1px solid #DEE2CF");
    delB->setStyleSheet("background: #DEE2CF;");
    delB->setMinimumWidth(60);
    delB->setMaximumWidth(60);
    delB->setMinimumHeight(25);
    delB->setMaximumHeight(25);
    connect(delB, SIGNAL (released()), this, SLOT (deleteMediumButton()));
    retlendB->setStyleSheet("background: #DEE2CF;");
    retlendB->setMinimumWidth(80);
    retlendB->setMaximumWidth(80);
    retlendB->setMinimumHeight(25);
    retlendB->setMaximumHeight(25);
    connect(retlendB, SIGNAL (released()), this, SLOT (retlendMediumButton()));
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
    return medium->getID();
}

int MainWindow::addPerson(QString pName, int pID){
    QString pEntry;
    Person *person = new Person(pName);
    // Person in Liste erfassen
    if (pID == -1){
        lendlib->addPersonToList(person);
    } else {
        if (!lendlib->addPersonToList(person, pID)){
            otherErr = true;
            errString = "Person konnte nicht mit vorgegebener ID eingegeben werden.";
            checkError();
        }
    }

    pEntry = QString::number(person->getID());

    // UI-Elemente erstellen
    QWidget *newPerson = new QWidget;
    QHBoxLayout *newPersonLayout = new QHBoxLayout(newPerson);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *name = new QLabel(pName);
    QWidget *lent = new QWidget;
    new QVBoxLayout(lent);

    // UI-Eigenschaften
    newPerson->setObjectName(pEntry);   // alle Medien-Widgets haben die Bezeichnung der ID
    delB->setObjectName("del"+pEntry);
    delB->setToolTip("Lösche Person "+pEntry+": "+pName);
    name->setObjectName("name"+pEntry);
    lent->setObjectName("lent"+pEntry);

    newPerson->layout()->setMargin(0);
    newPerson->setStyleSheet("border-bottom: 1px solid #DEE2CF");
    lent->layout()->setMargin(0);
    delB->setStyleSheet("background: #DEE2CF;");
    delB->setMinimumWidth(60);
    delB->setMaximumWidth(60);
    delB->setMinimumHeight(25);
    delB->setMaximumHeight(25);
    connect(delB, SIGNAL (released()), this, SLOT (deletePersonButton()));
    lent->setMaximumWidth(250);

    newPersonLayout->addWidget(delB);
    newPersonLayout->addWidget(name);
    newPersonLayout->addWidget(lent);
    qobject_cast<QVBoxLayout*>(ui->allPersonsScroll->layout())->insertWidget(-1,newPerson);

    ui->allPersonsScroll->layout()->removeItem(ui->personSpacer);
    ui->allPersonsScroll->layout()->addItem(ui->personSpacer);
    return person->getID();
}

void MainWindow::lendMedium(int mediumID, int personID){
    // Zur Bibliothek hinzufügen
    lendlib->addLendEntry(mediumID, personID);
    // ins GUI einfügen
    QString mediumIDs = QString::number(mediumID);
    QString personIDs = QString::number(personID);
    QString mediumS = lendlib->getMediumEntry(mediumID)->getTitle();
    QString personS = lendlib->getPersonEntry(personID)->getFullName();
    ui->allMediaScroll->findChild<QLabel*>("lendee"+mediumIDs)->setText(personS);
    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setText("Zurück geben");
    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setToolTip("Gebe Medium "+mediumIDs+" zurück.");
    QString type = "";
    MType mType =  lendlib->getMediumEntry(mediumID)->getType();
    switch (mType){
    case book:
        type=" (Buch)";
        break;
    case cd:
        type=" (CD)";
        break;
    case dvd:
        type=" (DVD)";
        break;
    }
    QLabel *lentItem = new QLabel(mediumS+type);
    lentItem->setObjectName("lentItem"+mediumIDs);
    ui->allPersonsScroll->findChild<QWidget*>("lent"+personIDs)->layout()->addWidget(lentItem);
}

void MainWindow::returnMedium(int mediumID){
    // aus Bibliothek austragen
    lendlib->removeLendEntry(mediumID);
    // aus GUI austragen
    QString mediumIDs = QString::number(mediumID);
    QString mediumS = lendlib->getMediumEntry(mediumID)->getTitle();

    ui->allMediaScroll->findChild<QLabel*>("lendee"+mediumIDs)->setText("");
    delete ui->allPersonsScroll->findChild<QLabel*>("lentItem"+mediumIDs);

    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setText("Ausleihen");
    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setToolTip("Leihe Medium "+mediumIDs+" aus: "+mediumS);

}

void MainWindow::deleteMedium(int mediumID){
    // aus Bibliothek löschen
    lendlib->removeLendEntry(mediumID);
    lendlib->deleteMedium(mediumID);
    // aus GUI löschen
    QString mediumIDs = QString::number(mediumID);
    QWidget *mEntry = ui->allMediaScroll->findChild<QWidget*>(mediumIDs);
    ui->allMediaScroll->layout()->removeWidget(mEntry);
    delete mEntry;
    // auch aus der Liste in Personen löschen
    QWidget *pEntry = ui->allPersonsScroll->findChild<QWidget*>("lentItem"+mediumIDs);
    if (!pEntry == NULL){
        ui->allMediaScroll->layout()->removeWidget(pEntry);
        delete pEntry;
    }

    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);
}

void MainWindow::deletePerson(int personID){
    // aus Bibliothek löschen
    lendlib->deletePerson(personID);
    // aus GUI löschen
    QString personIDs = QString::number(personID);
    QWidget *pEntry = ui->allPersonsScroll->findChild<QWidget*>(personIDs);
    ui->allPersonsScroll->layout()->removeWidget(pEntry);
    delete pEntry;
    // alle Ausleiheinträge löschen:
    QList<int> mList = lendlib->getLendMedia(personID);
    for (auto m: mList){
        returnMedium(m);
    }
}



MainWindow::~MainWindow(){
    saveLibToFile();
    delete ui;
}

