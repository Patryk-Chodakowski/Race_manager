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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(Game &g,QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

    void on_pushButton_normal_clicked();

    void on_pushButton_speedUp_clicked();

    void on_pushButton_slowDown_clicked();

    void refreshPanel();
    void diablePitStop();
    void enablePitstop();
    void finishRace();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    void setLapLabel();

    Simulation *race;
    Game *game;
    V_Map *map;

    PlayersWidget ** playerWidget;
    QGraphicsScene *scene;

    void updateLabels();
    void togglePitLabel();
};
#endif // MAINWINDOW_H
