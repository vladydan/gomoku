#ifndef MINMAX_HH_
# define MINMAX_HH_

#include <iostream>
# include <vector>
# include <cmath>
# include <algorithm>

#include "Player.hpp"
#include "Game.hpp"

#define COORD(x, y)	(y * Y_SIZE + x)

typedef struct	coords
{
  int		y;
  int		x;
  int		value;
}		coords;


class MinMax
{
public:
  static std::vector<coords>		getNextMove(unsigned long long *board, Player playing, Player opponent);
  static int		alphaBeta(unsigned long long *board, std::vector<coords> const &coordinates, short depth,
				  bool maximisingPlayer, Player playing, Player opponent, int alpha, int beta);
};

#endif /* !MINMAX_HH_ */
