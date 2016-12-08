#ifndef MINMAX_HH_
# define MINMAX_HH_

#include <iostream>
# include <vector>
# include <cmath>
# include <algorithm>
#include <cstdlib>

#include "Player.hpp"
#include "Game.hpp"

#define COORD(x, y)	(y * Y_SIZE + x)
#define DEPTH 4

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
    static std::vector<coords>		algo(unsigned long long *board, Player playing, Player opponent, bool bF);
  static int		alphaBeta(unsigned long long *board, short depth,
				  bool maximisingPlayer, Player playing, Player opponent, int alpha, int beta, bool bF);
};

#endif /* !MINMAX_HH_ */
