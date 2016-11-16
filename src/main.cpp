#include "GomokuWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  if (argc > 1)
    {
      Player	one(BLACK, "Bob", Player::PLAYER);
      Player	two(WHITE, "Baba", Player::PLAYER);
      Game	game(&one, &two, true, true, NULL);
      game.playTerminal();
      return (0);
    }
  else
    {
      QApplication a(argc, argv);
      GomokuWindow w;
      w.show();
      return a.exec();
    }
}
