#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QLabel>

#include "qgraphicsarcitem.h"
//#include "simulation.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void refreshPanel();

private:
    Ui::MainWindow *ui;

    Simulation *race;
    Game game;
    V_Map *map;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsLineItem *line;
    QGraphicsArcItem *arc;

    QLabel **description;

    void updateLabels();
    void togglePitLabel();
};
#endif // MAINWINDOW_H
