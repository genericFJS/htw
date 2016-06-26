#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mediumtype.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void deleteItemButton();
    void lendItemButton();

private:
    Ui::MainWindow *ui;
    void initUI();
    void addMediumUI(MType mType, QString mName);
};

#endif // MAINWINDOW_H
