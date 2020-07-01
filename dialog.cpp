#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->setFixedSize(this->width(),this->height());
    ui->setupUi(this);

    scene = new QGraphicsScene(this);


//    V_Map *map = new V_Map();
//    map->draw_map(scene);


//    QGraphicsItem *luk;
//    int start = 90 * 16;
//    int end = 270 * 16;
//    QPainter *arc;
//    arc->drawArc(200,200,40,50,start,end);
    //luk = scene->addItem(arc);


//    arc = new QGraphicsArcItem(0,0,200);
    //    line = scene->addLine(100,100,200,400,outlinePen);


//    scene->addItem(arc);




    //rectangle = scene->addRect(200, 0, 80, 100, outlinePen, blueBrush);

    // addEllipse(x,y,w,h,pen,brush)
    //ellipse = scene->addEllipse(300, 0, 300, 60, outlinePen, greenBrush);


}

Dialog::~Dialog()
{
    delete scene;
    delete arc;
    delete rectangle;
    delete line;
    delete ui;
}
