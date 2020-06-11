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
    ui->graphicsView->setScene(scene);

    QBrush greenBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);


    QGraphicsItem *luk;
    int start = 90 * 16;
    int end = 270 * 16;
    QPainter *arc;
    arc->drawArc(200,200,40,50,start,end);

    //luk = scene->addItem(arc);

    rectangle = scene->addRect(50, 0, 80, 100, outlinePen, blueBrush);

    // addEllipse(x,y,w,h,pen,brush)
    ellipse = scene->addEllipse(100, 0, 300, 60, outlinePen, greenBrush);

    QGraphicsLineItem *line;

    line = scene->addLine(100,100,200,400,outlinePen);
}

Dialog::~Dialog()
{
    delete ui;
}
