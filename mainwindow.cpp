#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("OFF");

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,1400,700);

    race = game.getSimulation();
    map = new V_Map(race->get_trail());
    map->draw_map(scene);
    race->getPlayers();


    for(auto player: (*race->getPlayers())){
        map->draw_vehicle(scene,player->getCar());
    };

    int nr_players = race->getPlayers()->size();
//    playerGrid = new QGridLayout*[nr_players];

//    description = new QLabel*[nr_players];

    playerWidget = new PlayersWidget*[nr_players];

    for (int i=0 ; i< nr_players;i++){

        playerWidget[i] = new PlayersWidget(race->getPlayers()->at(i),this);

        ui->horizontalLayout->addWidget(playerWidget[i]);

//        playerGrid[i] = new QGridLayout(this);

//        QLabel *label = new QLabel();
//        QString text = race->getPlayers()->at(i)->getName().c_str();
//        text += " ";
//        text += QString::number(race->getPlayers()->at(i)->getCar()->getDistance());
//        label->setText(text);
//        label->setStyleSheet("border: 5px solid " + race->getPlayers()->at(i)->getPlayerColorName());

//        playerGrid[i]->addWidget(label);

//        ui->horizontalLayout->addLayout(playerGrid[i]);

//        description[i] = new QLabel(this);
//        QString text = race->getPlayers()->at(i)->getName().c_str();
//        text += " ";
//        text += QString::number(race->getPlayers()->at(i)->getCar()->getDistance());
//        description[i]->setText(text);
//        description[i]->setStyleSheet("border: 5px solid " + race->getPlayers()->at(i)->getPlayerColorName());
//        ui->horizontalLayout->addWidget(description[i]);
    }


    race->setVehiclesOnStart();


    connect(race,SIGNAL(updateView()),this,SLOT(refreshPanel()));

//    scene->invalidate();

//    race = new Simulation();

//    race->get_map()->draw_map(scene);
//    race->get_map()->draw_vehicle(scene,race->get_vehicles());
//    race->setVehiclesOnStart();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Vehicle *v = race->get_human()->getCar();
    v->setGoToPitStop(true);
    togglePitLabel();
}

void MainWindow::togglePitLabel(){
   if(ui->label->text() == "OFF") ui->label->setText("ON");
   else ui->label->setText("OFF");
   ui->label->update();
}

void MainWindow::on_pushButton_3_clicked()
{
//    Vehicle *v = race->get_vehicles();
//    int t = v->get_track();
//    t++;
//    if (t>1) t = 1;
//    v->set_track(t);

    race->get_human()->getCar()->set_track(1);
}

void MainWindow::on_pushButton_2_clicked()
{
//    Vehicle *v = race->get_vehicles();
//    int t = v->get_track();
//    t--;
//    if (t<-1) t = -1;
//    v->set_track(t);

    race->get_human()->getCar()->set_track(-1);
}

void MainWindow::on_pushButton_4_clicked()
{
    race->makeMoves();
    updateLabels();
//    ui->graphicsView->update();
}

void MainWindow::refreshPanel()
{
    updateLabels();
}

void MainWindow::updateLabels()
{
    int nr_players = race->getPlayers()->size();

    for (int i=0 ; i< nr_players;i++){
//        QString text = race->getPlayers()->at(i)->getName().c_str();
//        text += " ";
//        text += QString::number(race->getPlayers()->at(i)->getCar()->getDistance());

//        description[i]->setText(text);
//        description[i]->update();
          playerWidget[i]->updateWidget();

//        ui->horizontalLayout->addWidget(description[i]);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    race->simStart();
}

void MainWindow::on_pushButton_6_clicked()
{
    race->simPause();
}

void MainWindow::on_pushButton_7_clicked()
{
    Vehicle *v = race->get_human()->getCar();
    v->toggleRun();

}

void MainWindow::on_pushButton_8_clicked()
{
    race->get_human()->getCar()->set_track(0);
}
