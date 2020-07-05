#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->setFixedSize(this->width(),this->height());
    ui->setupUi(this);

    human = game.getHuman();

    ui->table->setColumnWidth(0,100);
    ui->table->setColumnWidth(1,60);

    updateDialog();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateDialog()
{
    ui->player_name->setText(human->getName().c_str());
    ui->money->setText(QString::number(human->getMoney()));

    ui->tank->setText(QString::number(human->getCar()->getFuelTankCapacity()));
    ui->velocity->setText(QString::number(human->getCar()->getMaxVelocity()));

    ui->vehicle_upgrade_cost->setText(QString::number(human->vehicleUpgradeCost()));

    ui->engineers_level->setText(QString::number(human->getTeam()->getEngineers()+1));
    ui->engineers_upgrade_cost->setText(QString::number(human->teamUpgradeCost()));

    ui->table->clearContents();
    int size = ui->table->rowCount();

    for (int i=size;i>=0;i--){
        ui->table->removeRow(i);
    }

    QLabel l[game.getPlayers()->size()];
    int i = 0;
    for (auto& p: *(game.getPlayers())){
        ui->table->insertRow(i);
        ui->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(p->getName())));
        ui->table->setItem(i,1,new QTableWidgetItem(QString::number(p->getPoints())));
        i++;
    };

    ui->table->sortItems(0);
    ui->table->sortItems(1,Qt::DescendingOrder);

    ui->race->setText(game.getRaceName().c_str());



    if (game.getCurrRace() >= game.getRaceLimit()){
        //koniec gry
        ui->pushButton_race->setDisabled(true);

        QMessageBox msg(this);
        msg.setWindowTitle("Komunikat");
        msg.setText("Koniec gry! Zajęto " + QString::number(game.getHumanStanding()) + " pozycję!");
        msg.exec();
    };
}

void Dialog::on_pushButton_race_clicked()
{
    game.prepareSimulation();

    window = new MainWindow(game);
    connect(window,SIGNAL(destroyed()),this,SLOT(raceClosed()));
    window->showMaximized();
    hide();
}

void Dialog::on_pushButton_tank_clicked()
{
    QString txt = "";
    int cost = human->vehicleUpgradeCost();

    if (human->getCar()->getTankUpgrage() > 1){
        txt = "Osiągnięto maksymalny poziom";
    } else if (human->getMoney() < cost){
        txt = "Niewystarczający budżet";
    } else {
        human->changeMoney(human->getMoney() - cost);
        human->getCar()->upgradeTank(human->getCar()->getTankUpgrage() + 1);
        txt = "Ulepszono pojazd";
    }

    QMessageBox msg(this);
    msg.setWindowTitle("Komunikat");
    msg.setText(txt);
    msg.exec();

    updateDialog();
}

void Dialog::on_pushButton_team_clicked()
{
    QString txt = "";
    int cost = human->teamUpgradeCost();

    if (human->getTeam()->getEngineers() > 1){
        txt = "Osiągnięto maksymalny poziom";
    } else if (human->getMoney() < cost){
        txt = "Niewystarczający budżet";
    } else {
        human->changeMoney(human->getMoney() - cost);
        human->getTeam()->upgradeEngineers();
        txt = "Ulepszono zespół";
    }

    QMessageBox msg(this);
    msg.setWindowTitle("Komunikat");
    msg.setText(txt);
    msg.exec();

    updateDialog();
}

void Dialog::raceClosed()
{
    show();
    updateDialog();
}
