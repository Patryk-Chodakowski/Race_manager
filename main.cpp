#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <iostream>

#include "trail.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Trail t;
    t.create_elements();


    Dialog d;
    d.show();

    return a.exec();
}
