#ifndef MINMAX_HH_
# define MINMAX_HH_

#include <iostream>
# include <vector>
# include <stdio.h>      /* printf, scanf, puts, NULL */
# include <stdlib.h>     /* srand, rand */
# include <time.h>       /* time */
# include <math.h>
# include <algorithm>

# define X_SIZE 2
# define Y_SIZE 2

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
  static coords		getNextMove();
  static int		alphaBeta(unsigned long long *board, std::vector<coords> const &coordinates, short depth,
				  bool maximisingPlayer);
};

#endif /* !MINMAX_HH_ */
