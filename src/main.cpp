#include "GomokuWindow.hpp"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    std::srand(time(NULL));
  if (argc > 1)
    {
      Player	one(BLACK, "Bob", Player::IA);
      Player	two(WHITE, "Baba", Player::IA);
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
