#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SFMLCanvas.hpp"
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

private slots:
    void on_exitButton_clicked();

    void on_pvpButton_clicked();

    void on_actionExit_triggered();

    void on_settingsButton_clicked();

    void on_backToMenuButton_clicked();

    void on_actionBack_to_the_menu_triggered();

private:
    Ui::GomokuWindow *ui;
    SFMLCanvas *sfmlCanvas;
    QStackedWidget *stackedWidget;
    Game *currentGame;
    Player *playerOne;
    Player *playerTwo;
};

#endif // MAINWINDOW_H
