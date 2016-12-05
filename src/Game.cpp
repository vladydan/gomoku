#include <cstring>
#include "Game.hpp"
#include "SFMLCanvas.hh"

aroundCases	around[] =
  { {UP, UPDEC, 0, -1, DOWN, DOWNDEC, UP_OFF, DOWN_OFF},
    {UPRIGHT, UPRIGHTDEC, 1, -1, DOWNLEFT, DOWNLEFTDEC, UPRIGHT_OFF, DOWNLEFT_OFF},
    {RIGHT, RIGHTDEC, 1, 0, LEFT, LEFTDEC, RIGHT_OFF, LEFT_OFF},
    {DOWNRIGHT, DOWNRIGHTDEC, 1, 1, UPLEFT, UPLEFTDEC, DOWNRIGHT_OFF, UPLEFT_OFF},
    {DOWN, DOWNDEC, 0, 1, UP, UPDEC, DOWN_OFF, UP_OFF},
    {DOWNLEFT, DOWNLEFTDEC, -1, 1, UPRIGHT, UPRIGHTDEC, DOWNLEFT_OFF, UPRIGHT_OFF},
    {LEFT, LEFTDEC, -1, 0, RIGHT, RIGHTDEC, LEFT_OFF, RIGHT_OFF},
    {UPLEFT, UPLEFTDEC, -1, -1, DOWNRIGHT, DOWNRIGHTDEC, UPLEFT_OFF, DOWNRIGHT_OFF},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };

Game::Game(Player *one, Player *two, bool bF, bool dTF, SFMLCanvas *sfml)
{
  memset(_board, 0, sizeof(_board));
  _playing = true;
  _players[0] = one;
  _players[1] = two;
  _turn = 0;
  _breakableFive = bF;
  _doubleThreeFree = dTF;
  _winner = NULL;
  _sfml = sfml;
}

void    Game::setBreakableFive(bool state)
{
  this->_breakableFive = state;
}

void    Game::setDoubleThreeFree(bool state)
{
  this->_doubleThreeFree = state;
}

unsigned long long	Game::getValue(unsigned long long *board, int const& x, int const& y, unsigned long long const& mask, int const& decal)
{
  if (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE)
    return ((board[COORD(x, y)] & mask) >> decal);
  return (0);
}

void	Game::changeValue(unsigned long long *board, int const& x, int const& y, unsigned long long const& mask, int const& decal, unsigned long long const& value)
{
  if (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE)
    {
      board[COORD(x, y)] &= ~mask;
      board[COORD(x, y)] |= value << decal;
    }
}

void	Game::printBoard(unsigned long long *board)
{
  for (int y = 0; y < Y_SIZE ; ++y)
    {
      for (int x = 0 ; x < X_SIZE ; ++x)
	{
	  if (getValue(board, x, y, EMPTYMASK, 0) == 0)
	    std::cout << '.';
	  else
	    std::cout << getValue(board, x, y, COLORMASK, 1);
	}
      std::cout << std::endl;
    }
}

std::list<freeThree>	Game::getfreeThreeList(unsigned long long *board, int const& x, int const& y)
{
  int			i = 0;
  unsigned long long	color = getValue(board, x, y, COLORMASK, 1);
  std::list<freeThree>	list;

  while (around[i].mask != 0)
    {
      if (checkCase(x + 3 * around[i].x, y + 3 * around[i].y) &&
	  checkCase(x + around[around[i].opp_off].x, y + around[around[i].opp_off].y) &&
	  getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) == 0 &&
	  getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
	  getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color &&
	  getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
	  getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
	  getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) == 0)
	{
	  freeThree	var;
	  var.cases[0] = {x, y};
	  var.cases[1] = {x + around[i].x, y + around[i].y };
	  var.cases[2] = {x + 2 * around[i].x, y + 2 * around[i].y };
	  list.push_back(var);
	}
      else if (checkCase(x + 2 * around[i].x, y + 2 * around[i].y) &&
	       checkCase(x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y) &&
	       getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) == 0 &&
	       getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
	       getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color &&
	       getValue(board, x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y, EMPTYMASK, 0) == 0 &&
	       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) != 0 &&
	       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) == color)
	{
	  freeThree	var;
	  var.cases[0] = {x + around[i].x, y + around[i].y };
	  var.cases[1] = {x, y };
	  var.cases[2] = {x + around[around[i].opp_off].x, y + around[around[i].opp_off].y };
	  list.push_back(var);
	}
      else if (checkCase(x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y) &&
	       checkCase(x + 3 * around[i].x, y + 3 * around[i].y) &&
	       getValue(board, x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y, EMPTYMASK, 0) == 0 &&
	       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) != 0 &&
	       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) == color &&
	       getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0 &&
	       getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
	       getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
	       getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) == 0)
	{
	  freeThree	var;
	  var.cases[0] = {x + around[around[i].opp_off].x, y + around[around[i].opp_off].y };
	  var.cases[1] = {x, y };
	  var.cases[2] = {x + 2 * around[i].x, y + 2 * around[i].y };
	  list.push_back(var);
	}
      else if (checkCase(x + 4 * around[i].x, y + 4 * around[i].y) &&
	       checkCase(x + around[around[i].opp_off].x, y + around[around[i].opp_off].y) &&
	       getValue(board, x + 4 * around[i].x, y + 4 * around[i].y, EMPTYMASK, 0) == 0 &&
	       getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) != 0 &&
	       getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, COLORMASK, 1) == color &&
	       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) == 0)
	{
	  if (getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) == 0 &&
	      getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
	      getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
	    {
	      freeThree	var;
	      var.cases[0] = {x, y };
	      var.cases[1] = {x + around[i].x, y + around[i].y };
	      var.cases[2] = {x + 3 * around[i].x, y + 3 * around[i].y };
	      list.push_back(var);
	    }
	  else if (getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
		   getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
		   getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0)
	    {
	      freeThree	var;
	      var.cases[0] = {x, y};
	      var.cases[1] = {x + 2 * around[i].x, y + 2 * around[i].y};
	      var.cases[2] = {x + 3 * around[i].x, y + 3 * around[i].y};
	      list.push_back(var);
	    }
	}
      ++i;
    }
  return (list);
}

bool	Game::checkdoubleInList(std::list<freeThree> & list)
{
  std::list<pos>	cases;

  for (std::list<freeThree>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      int	count = 0;
      for (int i = 0 ; i < 3 ; i++)
	{
	  for (std::list<pos>::iterator itc = cases.begin() ; itc != cases.end() ; itc++)
	    {
	      if (it->cases[i].x == itc->x && it->cases[i].y == itc->y)
		count += 1;
	    }
	}
      if (count == 1)
	return (true);
      for (int i = 0 ; i < 3 ; i++)
	{
	  bool	to_push = true;
	  for (std::list<pos>::iterator itc = cases.begin() ; itc != cases.end() ; itc++)
	    {
	      if (it->cases[i].x == itc->x && it->cases[i].y == itc->y)
		to_push = false;
	    }
	  if (to_push)
	    cases.push_back(it->cases[i]);
	}
    }
  return (false);
}

bool	Game::checkdoubleThree(unsigned long long *board, int const& x, int const& y, unsigned long long const& color)
{
  std::list<freeThree>	list;

  changeValue(board, x, y, COLORMASK, 1, color);
  changeValue(board, x, y, EMPTYMASK, 0, 1);
  list = getfreeThreeList(board, x, y);
  if (!checkdoubleInList(list))
    {
      for (std::list<freeThree>::iterator it = list.begin() ; it != list.end() ; it++)
	{
	  for (int i = 0 ; i < 3 ; i++)
	    {
	      if (it->cases[i].x != x || it->cases[i].y != y)
		{
		  std::list<freeThree>	l = getfreeThreeList(board, it->cases[i].x, it->cases[i].y);
		  if (checkdoubleInList(l))
		    {
		      std::cout << "double trois : " << it->cases[i].x << " " << it->cases[i].y << std::endl;
		      changeValue(board, x, y, COLORMASK, 1, 0);
		      changeValue(board, x, y, EMPTYMASK, 0, 0);
		      return (true);
		    }
		}
	    }
	}
    }
  else
    {
      std::cout << "double trois : " << x << " " << y << std::endl;
      changeValue(board, x, y, COLORMASK, 1, 0);
      changeValue(board, x, y, EMPTYMASK, 0, 0);
      return (true);
    }
  changeValue(board, x, y, COLORMASK, 1, 0);
  changeValue(board, x, y, EMPTYMASK, 0, 0);
  return (false);
}

bool	Game::checkBreakableFive(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;
  bool	broke;

  if ((board[COORD(x, y)] & BREAKABLE) != 0)
    return (true);
  while (i < 4)
    {
      broke = false;
      int	sideOne = (int) getValue(board, x, y, around[i].mask, around[i].decal);
      int	sideTwo = (int) getValue(board, x, y, around[i].opposite, around[i].opp_decal);
      if ((sideOne + sideTwo + 1) >= 5)
	{
	  int	m = 0;
	  for (m = 0 ; m < sideOne ; m++)
	    {
	      if (getValue(board, x + (m+1) * (around[i].x), y + (m+1) * (around[i].y), BREAKABLE, BREAKABLEDEC) != 0)
		{
		  broke = true;
		  break;
		}
	    }
	  int n = 0;
	  for (n = 0 ; n < sideTwo ; n++)
	    {
	    if (getValue(board, x + (n+1) * (around[around[i].opp_off].x), y + (n+1) * (around[around[i].opp_off].y), BREAKABLE, BREAKABLEDEC) != 0)
	      {
		broke = true;
		break;
	      }
	    } 
	  if (!broke || (m + n + 1) >= 5)
	    return (false);
	}
      ++i;
    }
  return (true);
}


bool	Game::checkEnd(unsigned long long *board, bool breakableFive)
{
/*  for (int i = 0 ; i < 2 ; i++)
    {
      if (_players[i]->getBroke() >= 10)
	{
	  _playing = false;
	  _winner = _players[i];
	  return;
	}
    }*/
  for (int y = 0; y < Y_SIZE ; ++y)
    {
      for (int x = 0; x < X_SIZE; ++x)
	{
	  if ((board[COORD(x, y)] & FIVEROW) != 0 && (!breakableFive || !checkBreakableFive(board, x, y)))
	    return (false);
	}
    }
	return (true);
}

bool	Game::checkCase(int const& x, int const& y)
{
  return (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE);
}

void	Game::deleteCase(unsigned long long *board, int const& x, int const& y, SFMLCanvas *sfml)
{
  int	i = 0;
  unsigned long long	color = getValue(board, x, y, COLORMASK, 1);
  unsigned long long	ar = getValue(board, x, y, AROUND, AROUNDDEC);

  changeAround(board, x, y);
  board[COORD(x, y)] = 0;
  if (sfml)
    sfml->removePiece(x, y);
  changeValue(board, x, y, AROUND, AROUNDDEC, ar);
  changeAligns(board, x, y);
  while (around[i].mask != 0)
    {
      if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 && getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
      {
	changeAligns(board, x + around[i].x, y + around[i].y);
	changeBreakable(board, x + around[i].x, y + around[i].y);
      }
      else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0)
	{
	  checkBreakable(board, x + around[i].x, y + around[i].y);
	  checkBreakable(board, x + 2 * around[i].x, y + 2 * around[i].y);
	}
      ++i;
    }
}

void	Game::affectBreakable(unsigned long long *board, int const& x, int const& y, Player *player, int i, SFMLCanvas *sfml)
{
  unsigned long long color = getValue(board, x, y, COLORMASK, 1);

  while (around[i].mask != 0)
    {
      if (checkCase(x + around[i].x, y + around[i].y) && (getValue(board, x + around[i].x, y + around[i].y, BREAKABLE_OFF, BREAKABLEOFFDEC) & (1 << around[i].opp_off)) != 0)
	{
	  if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 && getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
	    {
	      checkBreakable(board, x + around[i].x, y + around[i].y);
	      checkBreakable(board, x + 2 * (around[i].x), y + 2 * (around[i].y));
	    }
	  else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0)
	    {
	      affectBreakable(board, x, y, player, i + 1, sfml);
	      deleteCase(board, x + around[i].x, y + around[i].y, sfml);
	      deleteCase(board, x + 2 * (around[i].x), y + 2 * (around[i].y), sfml);
	      player->setBroke(player->getBroke() + 2);
	    }
	}
      ++i;
    }
}

void	Game::checkBreakable(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;
  unsigned long long color = getValue(board, x, y, COLORMASK, 1);
  bool	breakable = false;

  changeValue(board, x, y, BREAKABLE_OFF, BREAKABLEOFFDEC, 0); // reinit le breakableoff
  while (around[i].mask != 0)
    {
      if (checkCase(x + around[i].x, y + around[i].y) && checkCase(x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y)))
	{
	  if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0 &&
	      getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) != 0 &&
	      getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) == color &&
	      getValue(board, x + 2 *(around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y), EMPTYMASK, 0) != 0 &&
	      getValue(board, x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y), COLORMASK, 1) != color)
	    {
	      changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 1);
	      changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, BREAKABLE, BREAKABLEDEC, 1);
	      changeValue(board, x, y, ((unsigned long long)1 << (BREAKABLEOFFDEC + i)), BREAKABLEOFFDEC + i, 1);
	      changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, ((unsigned long long)1 << (BREAKABLEOFFDEC + i)), BREAKABLEOFFDEC  + i, 1);
	      breakable = true;
	    }
	  else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
		   getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) != color &&
		   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) != 0 &&
		   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) == color &&
		   getValue(board, x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y), EMPTYMASK, 0) == 0)
	    {
	      changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 1);
	      changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, BREAKABLE, BREAKABLEDEC, 1);
	      changeValue(board, x, y, ((unsigned long long)1 << (BREAKABLEOFFDEC + around[i].opp_off)), BREAKABLEOFFDEC + around[i].opp_off, 1);
	      changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, ((unsigned long long)1 << (BREAKABLEOFFDEC + around[i].opp_off)), BREAKABLEOFFDEC + around[i].opp_off, 1);
	      breakable = true;
	    }
	}
      ++i;
    }
  if (!breakable)
    changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 0);
}

void	Game::changeBreakable(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;
  unsigned long long color = getValue(board, x, y, COLORMASK, 1);

  while (around[i].mask != 0)
    {
      if (checkCase(x + around[i].x, y + around[i].y) && getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 && getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) != color)
	checkBreakable(board, x + around[i].x, y + around[i].y);
      ++i;
    }
  checkBreakable(board, x, y);
}

void	Game::changeFiveRow(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;
  unsigned long	long value;

  while (around[i].mask != 0)
    {
      value = getValue(board, x, y, around[i].mask, around[i].decal) + getValue(board, x, y, around[i].opposite, around[i].opp_decal) + 1;
      if (value >= 5)
	{
	  changeValue(board, x, y, FIVEROW, FIVEROWDEC, 1);
	  return;
	}
      ++i;
    }
  changeValue(board, x, y, FIVEROW, FIVEROWDEC, 0);
}

void	Game::changeAlignsAround(unsigned long long *board, int const& x, int const& y, unsigned long long const& color, int const& opp_x, int const& opp_y, aroundCases const& direction)
{
  if (x < 0 || x >= X_SIZE || y < 0 || y >= Y_SIZE)
    return;
  unsigned long long value;
  if (getValue(board, opp_x, opp_y, EMPTYMASK, 0) != 0)
    value = getValue(board, opp_x, opp_y, direction.opposite, direction.opp_decal) + 1;
  else
    value = 0;

  changeValue(board, x, y, direction.opposite, direction.opp_decal, value);
  changeFiveRow(board, x, y);
  if (checkCase(x + direction.x, y + direction.y) && getValue(board, x + direction.x, y + direction.y, EMPTYMASK, 0) != 0 && getValue(board, x + direction.x, y + direction.y, COLORMASK, 1) == color)
    changeAlignsAround(board, x + direction.x, y + direction.y, color, x, y, direction);
}

void	Game::changeAligns(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;
  unsigned long	long value;
  unsigned long	long color = getValue(board, x, y, COLORMASK, 1);

  if (getValue(board, x, y, EMPTYMASK, 0) != 0)
    {
      while (around[i].mask != 0)
	{
	  if (checkCase(x + around[i].x, y + around[i].y) && getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 && getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
	    {
	      value = getValue(board, x + around[i].x, y + around[i].y, around[i].mask, around[i].decal) + 1;
	      changeValue(board, x, y, around[i].mask, around[i].decal, value);
	    }
	  ++i;
	}
  i = 0;
  while (around[i].mask != 0)
    {
      if (checkCase(x + around[i].x, y + around[i].y) && getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 && getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
	changeAlignsAround(board, x + around[i].x, y + around[i].y, color, x, y, around[i]);
      ++i;
    }
  changeFiveRow(board, x, y);
    }
  else
    {
      while (around[i].mask != 0)
	{
	  if (checkCase(x + around[i].x, y + around[i].y) && getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0)
	    changeAlignsAround(board, x + around[i].x, y + around[i].y, getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1), x, y, around[i]);
	  ++i;
	}
    }
}

void	Game::changeAround(unsigned long long *board, int const& x, int const& y)
{
  int	i = 0;

  while (around[i].mask != 0)
    {
      if (checkCase(x + around[i].x, y + around[i].y))
    	{
	        changeValue(board, x + around[i].x, y + around[i].y, ZONE, ZONEDEC, 1);
	    }
        if (checkCase(x + 2 * around[i].x, y + 2 * around[i].y)) {
            changeValue(board, x + 2 * around[i].x, y + 2 * around[i].y, ZONE, ZONEDEC, 1);
        }
      ++i;
    }
}

int     Game::getTurn() const
{
  return this->_turn;
}

/*void		Game::printBoard()
{
  for (int y = 0 ; y < Y_SIZE ; y++)
    {
      for (int x = 0 ; x < X_SIZE ; x++)
	{
	  if (getValue(x, y, EMPTYMASK, 0) != 0)
	    std::cout << getValue(x, y, COLORMASK, 1) + 1;
	  else
	    std::cout << "0";
	}
      std::cout << std::endl;
    }
}*/

void		Game::playTerminal()
{
  int	x;
  int	y;
  int	color;

  while (_playing)
    {
      printBoard(_board);
      color = _players[_turn % 2]->getColor();
      std::cin >> x;
      std::cin >> y;
      if ((_board[COORD(x, y)] & EMPTYMASK) == 0 && (!_doubleThreeFree || !checkdoubleThree(_board, x, y, color)))
	{
	  changeValue(_board, x, y, COLORMASK, 1, color);
	  changeValue(_board, x, y, EMPTYMASK, 0, 1);
	  changeAround(_board, x, y);
	  changeAligns(_board, x, y);
	  affectBreakable(_board, x, y, _players[_turn % 2], 0, NULL);
	  changeBreakable(_board, x, y);
	  _playing = checkEnd(_board, _breakableFive);
	  if (_playing && _players[0]->getBroke() < 10 && _players[1]->getBroke() < 10)
	    _turn++;
	  else
	    {
	      if (_winner == NULL)
		_winner = _players[_turn % 2];
	    }
	}
    }
      printBoard(_board);
      std::cout << "Player : " << _winner->getName() << " wins!" << std::endl;
}

std::string	Game::play(unsigned int x, unsigned int y)
{
  int	color;

      color = _players[_turn % 2]->getColor();
      if ((_board[COORD(x, y)] & EMPTYMASK) == 0 && (!_doubleThreeFree || !checkdoubleThree(_board, x, y, color)))
	{
	  std::cout << x << " " << y << std::endl;
	  changeValue(_board, x, y, COLORMASK, 1, color);
	  changeValue(_board, x, y, EMPTYMASK, 0, 1);
	  changeAround(_board, x, y);
	  changeAligns(_board, x, y);
	  affectBreakable(_board, x, y, _players[_turn % 2], 0, _sfml);
	  changeBreakable(_board, x, y);
	  _playing = checkEnd(_board, _breakableFive);
	  //	  printBoard();
	  if (_playing && _players[0]->getBroke() < 10 && _players[1]->getBroke() < 10)
	    {
	      _turn++;
	      _sfml->updateStat("Turn : " + std::to_string(_turn), "Black : " + std::to_string(_players[0]->getBroke()), "White : "+ std::to_string(_players[1]->getBroke()));
	    }
	  else
	    {
	      if (_winner == NULL)
		_winner = _players[_turn % 2];
	      std::string winner = (_winner->getColor() == BLACK ? "black" : "white");
	      _sfml->setWinner(winner);
	    }
	}
      else
	{
	  return ("null");
	}
  return (color == 0 ? "black" : "white");
}
