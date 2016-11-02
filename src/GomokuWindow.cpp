#include "GomokuWindow.hpp"
#include "ui_GomokuWindow.h"

GomokuWindow::GomokuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GomokuWindow),
    currentGame(nullptr),
    playerOne(nullptr),
    playerTwo(nullptr)
{
    ui->setupUi(this);
    QLabel *label = this->findChild<QLabel *>("menuTitle");
    label->setStyleSheet("QLabel { color : blue; }");
    this->findChild<QMenuBar *>("menuBar")->hide();
    this->stackedWidget = this->findChild<QStackedWidget *>("stackedWidget");
    sfmlCanvas = new SFMLCanvas(this->findChild<QFrame *>("sfmlFrame"), QPoint(20, 20), QSize(360, 360));
    sfmlCanvas->show();
    this->findChild<QFrame *>("sfmlFrame")->layout()->addWidget(sfmlCanvas);
}

GomokuWindow::~GomokuWindow()
{
    delete ui;
}

void GomokuWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void GomokuWindow::on_pvpButton_clicked()
{
    playerOne = new Player(BLACK, "Bob", Player::PLAYER);
    playerTwo = new Player(WHITE, "Baba", Player::PLAYER);
    currentGame = new Game(playerOne, playerTwo, true, true);
    this->findChild<QMenuBar *>("menuBar")->show();
    this->stackedWidget->setCurrentIndex(2);
    this->sfmlCanvas->setGame(currentGame);
}

void GomokuWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void GomokuWindow::on_settingsButton_clicked()
{
  this->stackedWidget->setCurrentIndex(1);
}

void GomokuWindow::on_backToMenuButton_clicked()
{
  if (playerOne != nullptr)
  {
    delete playerOne;
    delete playerTwo;
    delete currentGame;
  }
  this->findChild<QMenuBar *>("menuBar")->hide();
  this->stackedWidget->setCurrentIndex(0);
}

void GomokuWindow::on_actionBack_to_the_menu_triggered()
{
  this->on_backToMenuButton_clicked();
}
