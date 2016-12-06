#include "MinMax.hh"

coords		MinMax::getNextMove()
{
  unsigned long long board[4];
  std::vector<coords> coord;
  for (int i = 0; i < 2; ++i)
    {
      for (int n = 0; n < 2; ++n)
	{
	  coords c;
	  c.y = i;
	  c.x = n;
	  coord.push_back(c);
	  board[(i*2) + n] = 0;
	}
    }

  srand(time(NULL));
  int val = -1;


  for (int i = 0, length = coord.size(); i < length; ++i)
    {
      int childValue = 0;
      std::vector<coords> newCoords;
      unsigned long long newBoard[Y_SIZE * X_SIZE];

      for (int n = 0, boardLength = Y_SIZE * X_SIZE; n < boardLength; ++n)
	newBoard[n] = board[n];

      for (int n = 0; n < length; ++n)
	{
	  int y = coord[n].y;
	  int x = coord[n].x;

	  if (n != i)
	    newCoords.push_back(coord.at(n));
	  else
	    newBoard[COORD(x, y)] = 2;		//ajouter une pierre noire a ces coordonnees
	}
      coord.at(i).value = MinMax::alphaBeta(board, coord, 4, false);
    }

  std::sort(coord.begin(), coord.end(),
	    [](const coords &first, const coords &second) -> bool
	    {
	      return first.value > second.value;
	    });

  for (int i = 0, length = coord.size(); i < length; ++i)
    std::cout << coord.at(i).value << std::endl;
}

int		MinMax::alphaBeta(unsigned long long* board, std::vector<coords> const &coordinates,
				  short depth, bool maximisingPlayer)
{
  int		bestValue = 0;

  if (depth == 0)
    {
      bestValue = rand() % 10 + 1;
      return (bestValue);
    }

  for (int i = 0, length = coordinates.size(); i < length; ++i)
    {
      int childValue = 0;
      std::vector<coords> newCoords;
      unsigned long long newBoard[Y_SIZE * X_SIZE];

      for (int n = 0, boardLength = Y_SIZE * X_SIZE; n < boardLength; ++n)
	newBoard[n] = board[n];

      for (int n = 0; n < length; ++n)
	{
	  int y = coordinates[n].y;
	  int x = coordinates[n].x;

	  if (n != i)
	    newCoords.push_back(coordinates.at(n));
	  else if (maximisingPlayer)
	    newBoard[COORD(x, y)] = 1;		//ajouter une pierre blanche a ces coordonnees
	  else
	    newBoard[COORD(x, y)] = 2;		//ajouter une pierre noire a ces coordonnees
	}

      if (maximisingPlayer)
	{
	  childValue = alphaBeta(newBoard, newCoords, depth - 1, false);
	  if (bestValue == 0)
	    bestValue = childValue;
	  else
	    bestValue = fmax(bestValue, childValue);
	}
      else
	{
	  childValue = alphaBeta(newBoard, newCoords, depth - 1, true);
	  if (bestValue == 0)
	    bestValue = childValue;
	  else
	    bestValue = fmin(bestValue, childValue);
	}
    }
  return (bestValue);
}
