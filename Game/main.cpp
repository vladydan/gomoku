#include "Game.hpp"
#include "Player.hpp"

int	main()
{
  Player	one(BLACK, "Bob", Player::PLAYER);
  Player	two(WHITE, "Baba", Player::PLAYER);
  Game		game(&one, &two, true, true);
  game.play();
}
