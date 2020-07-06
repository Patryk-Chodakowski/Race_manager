#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

#include "qgraphicsarcitem.h"
#include "playerswidget.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
\brief Okno wyścigu
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(Game &g,QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    ///\brief Przycisk PitStop
    void on_pushButton_clicked();

    ///\brief Przycisk Normalnej prędkości
    void on_pushButton_normal_clicked();

    ///\brief Przycisk Przyspieszenia pojazdu
    void on_pushButton_speedUp_clicked();

    ///\brief Przycisk Spowolnienia pojazdu
    void on_pushButton_slowDown_clicked();

    ///\brief Odświerza panel danych o uczestnikach wyscigu
    void refreshPanel();

    ///\brief Blokuje przycisk PitStop
    void diablePitStop();

    ///\brief Aktywuje przycisk PitStop
    void enablePitstop();

    ///\brief Kończy wyścig i rozdaje punkty
    void finishRace();

    ///\brief Przycisk powrotu
    void on_back_clicked();

    ///\brief Przycisk pauzy
    void on_pause_clicked();

    ///\brief Przycisk startu
    void on_start_clicked();

    void on_cheat_clicked();

private:
    Ui::MainWindow *ui;

    ///\brief Aktualizuje licznik okrążeń
    void setLapLabel();

    /// Wskaźnik na wyścig
    Simulation *race;
    /// Wskaźnik na grę
    Game *game;
    /// Wskaźnik na mapę
    V_Map *map;

    /// Wskaźnik na tablicę dynamiczą obieków prezentujących stan uczestników
    PlayersWidget ** playerWidget;
    /// Wskaźnik na scenę
    QGraphicsScene *scene;

    ///\brief Aktualizuje widżety ze stanem uczestników
    void updateLabels();
};
#endif // MAINWINDOW_H
