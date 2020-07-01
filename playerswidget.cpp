#include "playerswidget.h"
#include "ui_playerswidget.h"

PlayersWidget::PlayersWidget(Player *p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersWidget)
{
    ui->setupUi(this);
    player = p;

//    ui->verticalLayout->setParent(ui->frame);
    vertical = new QVBoxLayout(ui->frame);
    horizontal = new QHBoxLayout();
    name = new QLabel();
    position = new QLabel();
    bar = new QProgressBar();

    name->setText(player->getName().c_str());
    name->setStyleSheet("");

    position->setText("Pozycja " + QString::number(player->getPlace()));


    bar->setTextVisible(false);
    bar->setMaximum(player->getCar()->getFuelTankCapacity());
    bar->setValue(player->getCar()->getFuelTankLevel());

    horizontal->addWidget(name);
    horizontal->addWidget(position);

    vertical->insertLayout(0,horizontal);
    vertical->addWidget(bar);

    ui->frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    ui->frame->setStyleSheet("QFrame {border: 5px solid " + player->getPlayerColorName() + "} QLabel,QHBoxLayout {border: none !important}");
}

PlayersWidget::~PlayersWidget()
{
    delete name;
    delete position;
    delete horizontal;
    delete bar;
    delete vertical;
    delete ui;
}

void PlayersWidget::updateWidget()
{
    bar->setValue(player->getCar()->getFuelTankLevel());
    bar->update();

    position->setText("Pozycja " + QString::number(player->getPlace()));
    position->update();
}
