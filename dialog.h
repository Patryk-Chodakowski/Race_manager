// dialog.h

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class Dialog;
}

/*!
\brief Okno menu startowego
*/

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    /*!
    \brief Odświerzenie wyświetlanych parametrów gracza w oknie
    */
    void updateDialog();

    /*!
    \brief Przycisk wywołania kolejnego wyścigu
    */
    void on_pushButton_race_clicked();

    /*!
    \brief Przycisk ulepszenia baku paliwa pojazdu
    */
    void on_pushButton_tank_clicked();

    /*!
    \brief Przycisk ulepszenia zespołu inżynierów
    */
    void on_pushButton_team_clicked();

    /*!
    \brief Funkcja otwierająca okno menu po zamknięciu okna wyścigu
    */
    void raceClosed();

private:
    Ui::Dialog *ui;

    ///Okno wyścigu
    MainWindow *window;

    ///Gra
    Game game;
    ///Wskaźnik na sterowany pojazd
    Player *human;
};
#endif // DIALOG_H
