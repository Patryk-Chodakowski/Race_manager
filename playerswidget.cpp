#include "playerswidget.h"
#include "ui_playerswidget.h"

PlayersWidget::PlayersWidget(Player *p,int _lapLimit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersWidget)
{
    ui->setupUi(this);
    player = p;
    lapLimit = _lapLimit;

//    ui->verticalLayout->setParent(ui->frame);
    vertical = new QVBoxLayout(ui->frame);
    horizontal = new QHBoxLayout();
    name = new QLabel();
    position = new QLabel();
    lap = new QLabel();
    bar = new QProgressBar();

    name->setText(player->getName().c_str());
    name->setStyleSheet("");

    position->setText("Pozycja " + QString::number(player->getPlace()));

    lap->setText(formatLaps());

    bar->setTextVisible(false);
    bar->setMaximum(player->getCar()->getFuelTankCapacity());
    bar->setValue(player->getCar()->getFuelTankLevel());

    horizontal->addWidget(name);
    horizontal->addWidget(position);

    vertical->insertLayout(0,horizontal);
    vertical->addWidget(lap);
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

    lap->setText(formatLaps());
    lap->update();
}

QString PlayersWidget::formatLaps()
{
    QString result("");
    int current = player->getCar()->getLap();

    if (current < 0) current = 0;
    if (current > lapLimit) result = "Okrążenia: koniec";
    else result = "Okrążenia: " + QString::number(current);


    return result;
}
