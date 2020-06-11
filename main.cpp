#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include "punkt.h"
#include <iostream>

#include "trasa.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Trasa t;
    t.tworz_elementy();


    Dialog d;
    d.show();

    return a.exec();
}
