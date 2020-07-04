#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(Game &g, QWidget *parent)
    :MainWindow(parent)
{
   game = &g;
   race = game->getSimulation();

   scene = new QGraphicsScene(this);
   ui->graphicsView->setScene(scene);
   scene->setSceneRect(0,0,1400,700);

   setAttribute(Qt::WA_DeleteOnClose);
   setWindowTitle(race->get_trail()->getName().c_str());

   map = new V_Map(race->get_trail());
   map->draw_map(scene);

   for(auto& player: (*race->getPlayers())){
       map->draw_vehicle(scene,player->getCar());
   };

   race->setVehiclesOnStart();
   setLapLabel();
   on_pushButton_normal_clicked();

   int nr_players = race->getPlayers()->size();
   playerWidget = new PlayersWidget*[nr_players];

   for (int i=0 ; i< nr_players;i++){
       playerWidget[i] = new PlayersWidget(race->getPlayers()->at(i),race->get_trail()->getLaps(),this);
       ui->horizontalLayout->addWidget(playerWidget[i]);
   }

   connect(race,SIGNAL(updateView()),this,SLOT(refreshPanel()));
   connect(race,SIGNAL(disablePitButton()),this,SLOT(diablePitStop()));
   connect(race,SIGNAL(enablePitButton()),this,SLOT(enablePitstop()));
   connect(race,SIGNAL(raceEnded()),this,SLOT(finishRace()));
}

MainWindow::~MainWindow()
{
    for(auto& player: (*race->getPlayers())){
        map->removeVehicleFromScene(scene,player->getCar());
    };

    if (game->getSimulation()) game->getSimulation()->~Simulation();

    int nr_players = race->getPlayers()->size();

    for (int i=0 ; i< nr_players;i++) delete playerWidget[i];
    delete [] playerWidget;

    delete map;
    delete scene;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Vehicle *v = race->get_human()->getCar();
    if (v->turning_to_pitstop()){
        v->setGoToPitStop(false);
        ui->pushButton->setStyleSheet("");
    }else{
        v->setGoToPitStop(true);
        ui->pushButton->setStyleSheet("background-color: red");
    }
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
    setLapLabel();
//    ui->graphicsView->update();
}

void MainWindow::refreshPanel()
{
    updateLabels();
    setLapLabel();
}

void MainWindow::diablePitStop()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton->setStyleSheet("");
}

void MainWindow::enablePitstop()
{
    ui->pushButton->setEnabled(true);

}

void MainWindow::finishRace()
{
    QString txt = "";
    if (race->get_human()->getPlace() == 1) txt = "Gratulacje! Wygrano wyścig!";
    else txt = "Koniec wyścigu! Zajęto " + QString::number(race->get_human()->getPlace())  + " miejsce";;

    QMessageBox msg(this);
    msg.setWindowTitle("Komunikat");
    msg.setText(txt);
    msg.exec();

    game->nextRace();
    destroyed();
    close();
}

void MainWindow::updateLabels()
{
    int nr_players = race->getPlayers()->size();

    for (int i=0 ; i< nr_players;i++){
          playerWidget[i]->updateWidget();
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

void MainWindow::setLapLabel()
{
    int lap = race->getCurrentLap();
    int limit = race->get_trail()->getLaps();
    if (lap < 0) lap = 0;
    if (lap > limit) lap = limit;

    ui->label_lap->setText("Okrążenie " + QString::number(lap) + "/" + QString::number(limit));
    ui->label_lap->update();
}

void MainWindow::on_pushButton_normal_clicked()
{
    race->get_human()->getCar()->setRideStyle(0);
    ui->pushButton_speedUp->setStyleSheet("");
    ui->pushButton_slowDown->setStyleSheet("");
    ui->pushButton_normal->setStyleSheet("background-color: red");
}

void MainWindow::on_pushButton_speedUp_clicked()
{
    race->get_human()->getCar()->setRideStyle(1);

    ui->pushButton_slowDown->setStyleSheet("");
    ui->pushButton_normal->setStyleSheet("");
    ui->pushButton_speedUp->setStyleSheet("background-color: red");
}

void MainWindow::on_pushButton_slowDown_clicked()
{
    ui->pushButton_speedUp->setStyleSheet("");
    ui->pushButton_normal->setStyleSheet("");
    ui->pushButton_slowDown->setStyleSheet("background-color: red");

    race->get_human()->getCar()->setRideStyle(-1);
}

void MainWindow::on_pushButton_9_clicked()
{
    destroyed();
    close();
}
