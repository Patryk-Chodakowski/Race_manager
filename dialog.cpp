#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->setFixedSize(this->width(),this->height());
    ui->setupUi(this);

//    scene = new QGraphicsScene(this);





}

Dialog::~Dialog()
{
//    delete scene;
//    delete arc;
//    delete rectangle;
//    delete line;
    delete ui;
}



void Dialog::updateDialog()
{

}

void Dialog::on_pushButton_race_clicked()
{

}

void Dialog::on_pushButton_tank_clicked()
{

}

void Dialog::on_pushButton_team_clicked()
{

}
