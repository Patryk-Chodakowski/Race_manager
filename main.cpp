#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include "punkt.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    Dialog d;
    d.show();

    return a.exec();
}
