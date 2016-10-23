#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label = this->findChild<QLabel *>("menuTitle");
    label->setStyleSheet("QLabel { color : blue; }");
    this->findChild<QMenuBar *>("menuBar")->hide();
    this->stackedWidget = this->findChild<QStackedWidget *>("stackedWidget");
    SFMLCanvas* SFMLView = new SFMLCanvas(this->findChild<QFrame *>("sfmlFrame"), QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pvpButton_clicked()
{
    this->findChild<QMenuBar *>("menuBar")->show();
    this->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_settingsButton_clicked()
{
  this->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_backToMenuButton_clicked()
{
  this->findChild<QMenuBar *>("menuBar")->hide();
  this->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionBack_to_the_menu_triggered()
{
  this->on_backToMenuButton_clicked();
}
