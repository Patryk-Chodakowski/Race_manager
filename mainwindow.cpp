#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("OFF");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    race = game.getSimulation();

//    map = new V_Map(race->get_trail());

//    map->draw_map(scene);

//    race = new Simulation();

    race->get_map()->draw_map(scene);
    race->get_map()->draw_vehicle(scene,race->get_vehicles());
    race->setVehiclesOnStart();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    Vehicle *v = race->get_vehicles();
//    v->togglePitStop();
//    togglePitLabel();
}

void MainWindow::togglePitLabel(){
//   if(ui->label->text() == "OFF") ui->label->setText("ON");
//   else ui->label->setText("OFF");
//   ui->label->update();
}

void MainWindow::on_pushButton_3_clicked()
{
//    Vehicle *v = race->get_vehicles();
//    int t = v->get_track();
//    t++;
//    if (t>1) t = 1;
//    v->set_track(t);
}

void MainWindow::on_pushButton_2_clicked()
{
//    Vehicle *v = race->get_vehicles();
//    int t = v->get_track();
//    t--;
//    if (t<-1) t = -1;
//    v->set_track(t);
}
