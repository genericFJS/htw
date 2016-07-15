// Name: Falk-Jonatan Strube
// Matrikelnummer: 39467
// Studiengruppe: 15/041/61

#include "mainwindow.h"
/**
 * @brief MainWindow::MainWindow ist Konstruktor: initiert UI, liest .csv aus und füllt ggf. Demo-Daten ein.
 * @param parent
 */
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

/**
 * @brief MainWindow::fillDemoData befüllt Datenbank mit Demo-Daten, falls sie leer ist.
 * @param more wenn true, dann wird Datenbank auch befüllt, wenn bereits Daten in DB sind.
 */
void MainWindow::fillDemoData(bool more){
    QString addNo = "";
    if (more){
        qsrand( QDateTime::currentDateTime().toTime_t() );
        addNo = " ("+QString::number(qrand()%100)+")";
    }

    if (more || (lendlib->getMList().empty() && lendlib->getPList().empty())){
        int m1 = addMedium(book,"Die Bibel"+addNo,"");
        int m2 = addMedium(book,"Eragon"+addNo,"Christopher Paolini");
        addMedium(book,"Harry Potter"+addNo, "J. K. Rowling");
        int m4 = addMedium(cd,"Take That: Best of"+addNo, "Take That");
        int m5 = addMedium(dvd,"Harry Potter"+addNo, "Chris Columbus");
        int m6 =  addMedium(other,"Programmierung I Skript"+addNo,"");

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

/**
 * @brief MainWindow::initUI initiert die UI:
 */
void MainWindow::initUI(){
    /// Vorlagen löschen:
    ui->allMediaScroll->layout()->removeWidget(ui->mediaEntry1);
    delete ui->mediaEntry1;
    ui->allMediaScroll->layout()->removeWidget(ui->personEntry1);
    delete ui->personEntry1;

    /// Medium-Typ Auswahl füllen
    ui->addMediaType->addItem("-");
    ui->addMediaType->addItem("Buch");
    ui->addMediaType->addItem("CD");
    ui->addMediaType->addItem("DVD");

    /// Button verknüpfen
    connect(ui->addMediumButton, SIGNAL (released()), this, SLOT (addMediumButton()));
    connect(ui->addPersonButton, SIGNAL (released()), this, SLOT (addPersonButton()));
    connect(ui->addMediaType, SIGNAL (currentIndexChanged(int)), this, SLOT (changeMediaInput()));

    /// Detail-Eingabe verstecken
    ui->addMediaDetail->hide();
    ui->debug->hide();
}

/**
 * @brief MainWindow::checkError prüft, ob ein Fehler vorliegt (bspw. Lesefehler beim Lesen der .csv) und beendet das Program mit einem Hinweis, falls ja.
 */
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

/**
 * @brief MainWindow::fillLibFromFile füllt die Datenbank mit den Daten aus den entsprechenden .csv Dateien
 * (lendlibLend.csv für die Beziehung, lendlibMedia.csv für die Medien und lendlibPerson.csv für Personen)
 */
void MainWindow::fillLibFromFile(){
    QFile lendFile("lendlibLend.csv");
    QFile mFile("lendlibMedia.csv");
    QFile pFile("lendlibPerson.csv");
    QList<int> idList;
    /// Lese alle Medien aus
    if (mFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        mFile.readLine();
        while (!mFile.atEnd()) {
            QByteArray line = mFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            /// - Prüfe, ob Format richtig ist (4 Spalten)
            if (lineElements.length() == 4){
                int newID = lineElements[0].toInt();
                /// - Prüfe, ob ID in .csv korrekt ist
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
                /// - Füge Medium hinzu
                addMedium(mType,QString::fromStdString(lineElements[2].toStdString()),QString::fromStdString(lineElements[3].toStdString()),newID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibMedia.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 3 Elemente).";
                readErr = true;
                return;
            }
        }
    }
    /// Lese alle Personen aus
    if (pFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        pFile.readLine();
        while (!pFile.atEnd()) {
            QByteArray line = pFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            /// - Prüfe, ob Format richtig ist (2 Spalten)
            if (lineElements.length() == 2){
                int newID = lineElements[0].toInt();
                /// - Prüfe, ob ID in .csv korrekt ist
                if(idList.contains(newID)){
                    errString = "Fehler beim Lesen der Datei 'lendlibPerson.csv' in Zeile "+ QString::number(lineNumber)+" (ID bereits vorhanden).";
                    readErr = true;
                    return;
                }
                idList.append(newID);
                /// - Füge Person hinzu
                addPerson(QString::fromStdString(lineElements[1].toStdString()),newID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibPerson.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 2 Elemente).";
                readErr = true;
                return;
            }
        }
    }
    /// Lese alle Ausleih-Relationen aus
    if (lendFile.open(QIODevice::ReadOnly|QFile::Truncate)) {
        int lineNumber = 1;
        lendFile.readLine();
        while (!lendFile.atEnd()) {
            QByteArray line = lendFile.readLine().replace(QByteArray("\n"),QByteArray(""));
            lineNumber++;
            QList<QByteArray> lineElements = line.split('\t');
            /// - Prüfe, ob Format richtig ist (2 Spalten)
            if (lineElements.length() == 2){
                int mediumID = lineElements[0].toInt();
                int personID = lineElements[1].toInt();
                /// - Prüfe, ob die Medium-ID einem Medium entspricht
                if(!lendlib->isMediumEntry(mediumID)){
                    errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (ID ist kein Medium).";
                    readErr = true;
                    return;
                }
                /// - Prüfe, ob die Personen-ID einer Person entspricht
                if(!lendlib->isPersonEntry(personID)){
                    cerr << lineElements[0].toStdString() << " "<< mediumID << "\n";
                    cerr << lineElements[1].toStdString() << " "<< personID << "\n";
                    errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (ID ist keine Person).";
                    readErr = true;
                    return;
                }
                /// - Füge Ausleih-Relation hinzu
                lendMedium(mediumID, personID);
            } else {
                errString = "Fehler beim Lesen der Datei 'lendlibLend.csv' in Zeile "+ QString::number(lineNumber)+" (Zeile enthält nicht 2 Elemente).";
                readErr = true;
                return;
            }
        }
    }
}

/**
 * @brief MainWindow::saveLibToFile speichert die Datenbank in .csv Dateien
 */
void MainWindow::saveLibToFile(){
    QFile lendFile("lendlibLend.csv");
    QFile mFile("lendlibMedia.csv");
    QFile pFile("lendlibPerson.csv");
    /// Schreibe alle Personen
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
    /// Schreibe alle Medien
    if (mFile.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream stream(&mFile);
        QMap<int,Medium*> mList = lendlib->getMList();
        stream << "ID \t Typ \t Titel\n";
        for(auto m: mList.keys()){
            QString mDetail;
            switch (mList.value(m)->getType()){
            case book:
                mDetail = ((Book*)mList.value(m))->getAuthor();
                break;
            case cd:
                mDetail = ((CD*)mList.value(m))->getInterpret();
                break;
            case dvd:
                mDetail = ((DVD*)mList.value(m))->getDirector();
                break;
            default:
                mDetail = "";
            }
            stream << mList.value(m)->getID() << "\t" << mList.value(m)->getType() << "\t" << mList.value(m)->getTitle() << "\t" << mDetail << "\n";
        }
        mFile.close();
    }
    /// Schreibe alle Ausleih-Relationen
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

/**
 * @brief MainWindow::retlendMediumButton reagiert, wenn der Button zum Ausleihen/Zurückgeben gedrückt wurde und:
 */
void MainWindow::retlendMediumButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    int mediumID = sender()->parent()->objectName().toInt();
    if(!myB->text().compare("Ausleihen")){
        /// leiht entweder Medium aus, indem es den Nutzer eine Person auswählen lässt
        QStringList persons;
        QMap<int,Person*> allP = lendlib->getPList();
        for (auto p: allP.keys()){
            persons.append(allP.value(p)->getFullName()+"\t ID: "+QString::number(allP.value(p)->getID()));
        }
        bool ok;
        QString person = QInputDialog::getItem(this, "Ausleihen", "Ausleihen an:", persons, 0, false, &ok);
        if (ok && !person.isEmpty()){
            int personID = (person.split(" ID: ").last()).toInt();
            lendMedium(mediumID, personID);
        }
    } else {
        /// oder gibt das Medium zurückt
        returnMedium(mediumID);
    }
}

/**
 * @brief MainWindow::deleteMediumButton reagiert, wenn der Button zum Löschen eines Mediums gedrückt wurde
 */
void MainWindow::deleteMediumButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    /// und löscht das Medium
    deleteMedium(myB->parentWidget()->objectName().toInt());
}

/**
 * @brief MainWindow::deletePersonButton reagiert, wenn der Button zum Löschen einer Person gedrückt wurde
 */
void MainWindow::deletePersonButton(){
    QPushButton *myB = qobject_cast<QPushButton*>(sender());
    /// und löscht die Person
    deletePerson(myB->parentWidget()->objectName().toInt());
}

/**
 * @brief MainWindow::addMediumButton reagiert, wenn der Button zum Hinzufügen eines Mediums gedrückt wurde.
 */
void MainWindow::addMediumButton(){
    /// Setzt in jedem Fall ein Titel voraus.
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
        /// je nach Typ, wird ein anderes Medium erstellt
        addMedium(type, ui->addMediaTitle->text(), ui->addMediaDetail->text());
        ui->addMediaTitle->setText("");
        ui->addMediaDetail->setText("");
    }
}

/**
 * @brief MainWindow::addPersonButton reagiert, wenn der Button zum Hinzufügen einer Person gedrückt wurde.
 */
void MainWindow::addPersonButton(){
    /// Setzt in jedem Fall einen Namen voraus
    if(ui->addPersonName->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Bitte einen Namen eingeben.");
        msgBox.exec();
    } else {
        /// Fügt Person hinzu
        addPerson(ui->addPersonName->text());
        ui->addPersonName->setText("");
    }
}

/**
 * @brief MainWindow::changeMediaInput reagiert, wenn über die Auswahl-Box das Medium geändert wurde
 */
void MainWindow::changeMediaInput(){
    QString type = ui->addMediaType->currentText();
    /// und passt die Eingabefelder und Eingabehinweise an
    if (type.compare("Buch")==0){
        ui->addMediaDetail->show();
        ui->addMediaDetail->setPlaceholderText("Autor");
    } else if (type.compare("CD")==0){
        ui->addMediaDetail->show();
        ui->addMediaDetail->setPlaceholderText("Interpret");
    } else if (type.compare("DVD")==0){
        ui->addMediaDetail->show();
        ui->addMediaDetail->setPlaceholderText("Regisseur");
    } else{
        ui->addMediaDetail->setText("");
        ui->addMediaDetail->hide();
    }
}

/**
 * @brief MainWindow::addMedium fügt ein Medium in die Datenbank und ins UI ein
 * @param mType Typ des Mediums
 * @param mName Titel des Mediums
 * @param mID ID des Mediums, falls verfügbar (wenn leer, dann wird eine eigene erstellt)
 * @return ID des eingefügten Mediums
 */
int MainWindow::addMedium(MType mType, QString mName, QString detail, int mID){
    QString mTypeString;
    QString mEntry;
    Medium *medium;
    QString detailType;
    /// Unterscheidung zwischen Medien Typ: erstellt verschieden Klassen und füllt die Zusatzinformationen
    switch (mType){
    case book:
        mTypeString="Buch";
        medium = new Book(mName);
        ((Book*)medium)->setAuthor(detail);
        detailType="Autor: ";
        break;
    case cd:
        mTypeString="CD";
        medium = new CD(mName);
        ((CD*)medium)->setInterpret(detail);
        detailType="Interpret: ";
        break;
    case dvd:
        mTypeString="DVD";
        medium = new DVD(mName);
        ((DVD*)medium)->setDirector(detail);
        detailType="Regisseur: ";
        break;
    default:
        mTypeString="-";
        medium = new Medium(mName);
    }
    if (detail.isEmpty()){
        detail = "-";
        detailType = "";
    }
    /// Medium in Datenbank erfassen (Fehler, falls ID bereits existiert)
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

    /// UI-Elemente erstellen
    QWidget *newMedium = new QWidget;
    QHBoxLayout *newMediumLayout = new QHBoxLayout(newMedium);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *type = new QLabel(mTypeString);
    QLabel *title = new QLabel(mName);
    QLabel *lendee = new QLabel("");
    QPushButton *retlendB = new QPushButton("Ausleihen");

    /// UI-Eigenschaften anpassen
    newMedium->setObjectName(mEntry);
    newMedium->setToolTip("Typ: "+mTypeString+"\nTitel: "+mName+"\n"+detailType+detail);
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
    retlendB->setMinimumWidth(100);
    retlendB->setMaximumWidth(100);
    retlendB->setMinimumHeight(25);
    retlendB->setMaximumHeight(25);
    connect(retlendB, SIGNAL (released()), this, SLOT (retlendMediumButton()));
    type->setMinimumWidth(60);
    type->setMaximumWidth(60);
    lendee->setMinimumWidth(100);
    lendee->setMaximumWidth(100);

    newMediumLayout->addWidget(delB);
    newMediumLayout->addWidget(type);
    newMediumLayout->addWidget(title);
    newMediumLayout->addWidget(lendee);
    newMediumLayout->addWidget(retlendB);
    qobject_cast<QVBoxLayout*>(ui->allMediaScroll->layout())->insertWidget(getInsertPosition(mName),newMedium);

    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);
    return medium->getID();
}

/**
 * @brief MainWindow::addPerson fügt eine Person in die Datenbank und ins UI ein
 * @param pName Name der Person
 * @param pID ID der Person, falls verfügbar (wenn leer, dann wird eine eigene erstellt)
 * @return ID der Person
 */
int MainWindow::addPerson(QString pName, int pID){
    QString pEntry;
    Person *person = new Person(pName);
    /// Person in Liste erfassen (Fehler, falls ID bereits existiert)
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

    /// UI-Elemente erstellen
    QWidget *newPerson = new QWidget;
    QHBoxLayout *newPersonLayout = new QHBoxLayout(newPerson);
    QPushButton *delB = new QPushButton("Löschen");
    QLabel *name = new QLabel(pName);
    QWidget *lent = new QWidget;
    new QVBoxLayout(lent);

    /// UI-Eigenschaften anpassen
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
    qobject_cast<QVBoxLayout*>(ui->allPersonsScroll->layout())->insertWidget(getInsertPosition(pName,false),newPerson);

    ui->allPersonsScroll->layout()->removeItem(ui->personSpacer);
    ui->allPersonsScroll->layout()->addItem(ui->personSpacer);
    return person->getID();
}

/**
 * @brief MainWindow::lendMedium fügt Ausleih-Relation in Datenbank ein und passt UI an
 * @param mediumID ID des auszuleihenden Mediums
 * @param personID ID der Person, die Medium ausleiht
 */
void MainWindow::lendMedium(int mediumID, int personID){
    /// Zur Datenbank hinzufügen
    lendlib->addLendEntry(mediumID, personID);
    /// ins UI einfügen:
    QString mediumIDs = QString::number(mediumID);
    QString personIDs = QString::number(personID);
    QString mediumS = lendlib->getMediumEntry(mediumID)->getTitle();
    QString personS = lendlib->getPersonEntry(personID)->getFullName();
    /// - sowohl in Medienliste
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
    default:
        break;
    }
    QLabel *lentItem = new QLabel(mediumS+type);
    lentItem->setObjectName("lentItem"+mediumIDs);
    /// als auch in Personenliste
    ui->allPersonsScroll->findChild<QWidget*>("lent"+personIDs)->layout()->addWidget(lentItem);
}

/**
 * @brief MainWindow::returnMedium löscht Ausleih-Relation aus Datenbank und passt UI an
 * @param mediumID zu zurückgegebene Medium
 */
void MainWindow::returnMedium(int mediumID){
    /// aus Datenbank austragen
    lendlib->removeLendEntry(mediumID);
    /// aus UI austragen
    QString mediumIDs = QString::number(mediumID);
    QString mediumS = lendlib->getMediumEntry(mediumID)->getTitle();

    ui->allMediaScroll->findChild<QLabel*>("lendee"+mediumIDs)->setText("");
    delete ui->allPersonsScroll->findChild<QLabel*>("lentItem"+mediumIDs);

    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setText("Ausleihen");
    ui->allMediaScroll->findChild<QPushButton*>("retlend"+mediumIDs)->setToolTip("Leihe Medium "+mediumIDs+" aus: "+mediumS);

}

/**
 * @brief MainWindow::deleteMedium löscht Medium aus Datenbank und passt UI an
 * @param mediumID zu löschende Medium
 */
void MainWindow::deleteMedium(int mediumID){
    /// aus Bibliothek löschen
    lendlib->removeLendEntry(mediumID);
    lendlib->deleteMedium(mediumID);
    /// aus UI löschen
    QString mediumIDs = QString::number(mediumID);
    QWidget *mEntry = ui->allMediaScroll->findChild<QWidget*>(mediumIDs);
    ui->allMediaScroll->layout()->removeWidget(mEntry);
    delete mEntry;
    /// auch aus der Personenliste löschen
    QWidget *pEntry = ui->allPersonsScroll->findChild<QWidget*>("lentItem"+mediumIDs);
    if (pEntry){
        ui->allMediaScroll->layout()->removeWidget(pEntry);
        delete pEntry;
    }

    ui->allMediaScroll->layout()->removeItem(ui->mediaSpacer);
    ui->allMediaScroll->layout()->addItem(ui->mediaSpacer);
}

/**
 * @brief MainWindow::deletePerson löscht Person aus Datenbank und passt UI an
 * @param personID zu löschende Person
 */
void MainWindow::deletePerson(int personID){
    /// aus Datenbank löschen
    lendlib->deletePerson(personID);
    /// aus UI löschen
    QString personIDs = QString::number(personID);
    QWidget *pEntry = ui->allPersonsScroll->findChild<QWidget*>(personIDs);
    ui->allPersonsScroll->layout()->removeWidget(pEntry);
    delete pEntry;
    /// lösche auch Ausleih-Relation(en) dieser Person:
    QList<int> mList = lendlib->getLendMedia(personID);
    for (auto m: mList){
        returnMedium(m);
    }
}

/**
 * @brief MainWindow::getInsertPosition ermittelt die Position, an der ein neues Element (Medium/Person) in die Liste im UI eingefügt werden muss
 * @param entry Titel/Name, nach dem sortiert werden soll
 * @param isMedium  wenn true, wird es in die Medienliste eingetragen, sonst in die Personenliste
 * @return Position, an die Element eingefügt werden muss
 */
int MainWindow::getInsertPosition(QString entry, bool isMedium){
    int position = 0;
    if (isMedium){
        QMap<int,Medium*> mList = lendlib->getMList();
        QMapIterator<int,Medium*> mListI(mList);
        /// iteriert durch Liste und erhöht die Position für jeden Eintrag, der "kleiner" ist
        while (mListI.hasNext()){
            mListI.next();
            if (mListI.value()->getTitle().compare(entry, Qt::CaseInsensitive)<0)
                position++;
        }
    } else {
        QMap<int,Person*> pList = lendlib->getPList();
        QMapIterator<int,Person*> pListI(pList);
        while (pListI.hasNext()){
            pListI.next();
            if (pListI.value()->getFullName().compare(entry, Qt::CaseInsensitive)<0)
                position++;
        }
    }
    return position;
}

/**
 * @brief MainWindow::~MainWindow wird aufgerufen, wenn das Programm beendet wird und speichert die Datenbank in .csv-Dateien
 */
MainWindow::~MainWindow(){
    saveLibToFile();
    delete ui;
}

