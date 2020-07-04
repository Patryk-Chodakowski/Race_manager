#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "dialog.h"

int Player::instance_number = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog d;
    d.show();

    return a.exec();
}
