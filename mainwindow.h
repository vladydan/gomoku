#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SFMLCanvas.hpp"
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

    void on_pvpButton_clicked();

    void on_actionExit_triggered();

    void on_settingsButton_clicked();

    void on_backToMenuButton_clicked();

    void on_actionBack_to_the_menu_triggered();

private:
    Ui::MainWindow *ui;
    SFMLCanvas *sfmlCanvas;
    QStackedWidget *stackedWidget;
};

#endif // MAINWINDOW_H
