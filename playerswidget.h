#ifndef PLAYERSWIDGET_H
#define PLAYERSWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>

#include "player.h"

namespace Ui {
class PlayersWidget;
}

class PlayersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayersWidget(Player *p,int _lapLimit, QWidget *parent = nullptr);
    ~PlayersWidget();

    void updateWidget();

private:
    Ui::PlayersWidget *ui;

    int lapLimit = 0;
    QString formatLaps();

    QHBoxLayout *horizontal;
    QVBoxLayout *vertical;
    Player *player;
    QLabel *name, *position, *lap;
    QProgressBar *bar;
};

#endif // PLAYERSWIDGET_H
