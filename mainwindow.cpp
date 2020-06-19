#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    Simulation *race = new Simulation();
//    V_Map *map = new V_Map();

    race->get_map()->draw_map(scene);
    race->get_map()->draw_vehicle(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}

