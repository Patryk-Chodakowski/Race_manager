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

/*!
\brief Klasa widżetu prezentującego stan gracza: nazwę, kolor, okrążenie, pozycję, stan baku paliwa
*/

class PlayersWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
    \brief Konstuktor klasy
    \param *p Wskaźnik na gracza, którego ma opisywać widżet
    \param _lapLimit Liczba okrążeń w danym wyścigu
    \param *parent Rodzic elementu
    */
    explicit PlayersWidget(Player *p,int _lapLimit, QWidget *parent = nullptr);
    ~PlayersWidget();

    /*!
    \brief Odświerzenie widżetu
    */
    void updateWidget();

private:
    Ui::PlayersWidget *ui;

    ///liczba okrążeń w wyścigu
    int lapLimit = 0;
    ///\brief zwraca prawidłową liczbę okrążeń pojazdu (większą od 0 i mniejszą od liczby okążeń) lub koniec gdy ukończono wyścig
    QString formatLaps();

    QHBoxLayout *horizontal;
    QVBoxLayout *vertical;
    Player *player;
    QLabel *name, *position, *lap;
    QProgressBar *bar;
};

#endif // PLAYERSWIDGET_H
