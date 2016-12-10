#ifndef MINMAX_HH_
# define MINMAX_HH_

#include <iostream>
# include <vector>
# include <cmath>
# include <algorithm>
#include <cstdlib>

#include "Player.hpp"
#include "Game.hpp"

#define DEPTH 3

typedef struct	coords
{
  int		y;
  int		x;
  long long		value;
}		coords;


class MinMax
{
public:
    static std::vector<coords>		algo(unsigned long long *board, Player playing, Player opponent, bool bF);
    static long long		alphaBeta(unsigned long long *board, short depth,
    				  bool maximisingPlayer, Player playing, Player opponent, long long alpha, long long beta, bool bF);
};

#endif /* !MINMAX_HH_ */
