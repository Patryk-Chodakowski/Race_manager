// dialog.h

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void updateDialog();

    void on_pushButton_race_clicked();

    void on_pushButton_tank_clicked();

    void on_pushButton_team_clicked();

    void raceClosed();

private:
    Ui::Dialog *ui;

    MainWindow *window;

    Game game;
    Player *human;
};
#endif // DIALOG_H
