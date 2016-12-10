#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SFMLCanvas.hh"
#include "Game.hpp"
#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
class GomokuWindow;
}

class GomokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GomokuWindow(QWidget *parent = 0);
    ~GomokuWindow();

public slots:

  void on_actionBack_to_the_menu_triggered();
  void on_pvpButton_clicked();

private slots:
    void on_exitButton_clicked();

    void on_actionExit_triggered();

    void on_actionReplay_triggered();

    void on_doubleTrois_stateChanged(int arg1);

    void on_cinqCassble_stateChanged(int arg1);

    void on_IAButton_clicked();

private:
    Ui::GomokuWindow *ui;
    SFMLCanvas *sfmlCanvas;
    QStackedWidget *stackedWidget;
    Game *currentGame;
    Player *playerOne;
    Player *playerTwo;
};

#endif // MAINWINDOW_H
