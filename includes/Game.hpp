#pragma once

#include <iostream>
#include <list>
#include "Player.hpp"

#define X_SIZE 19
#define Y_SIZE 19

#define BLACK 0
#define WHITE 1

//MASKS
#define EMPTYMASK	1 
#define COLORMASK	2 // 10
#define FIVEROW		4 // 100
#define BREAKABLE	8 // 1000
#define FREETHREE	16 // 10000
#define AROUND		480 // 1 11100000
#define UP		3584 // 1110 00000000
#define UPRIGHT		28672 // 1110000 00000000
#define RIGHT		229376 // 11 10000000 00000000
#define DOWNRIGHT	1835008 // 11100 00000000 00000000
#define DOWN		14680064 // 11100000 00000000 00000000
#define DOWNLEFT	117440512 // 111 00000000 00000000 00000000
#define LEFT		939524096 // 111000 00000000 00000000 00000000
#define UPLEFT		7516192768 // 1 11000000 00000000 00000000 00000000
#define BREAKABLE_OFF	2190433320960 // 1 11111110 00000000 00000000 00000000 00000000

#define FIVEANDBREAK	12 // 1100
#define BLACKCASE	1
#define WHITECASE	3

//decal masks
#define FIVEROWDEC	2
#define BREAKABLEDEC	3
#define FREETHREEDEC	4
#define AROUNDDEC	5
#define UPDEC		9
#define UPRIGHTDEC	12
#define RIGHTDEC	15
#define DOWNRIGHTDEC	18
#define DOWNDEC		21
#define DOWNLEFTDEC	24
#define LEFTDEC		27
#define UPLEFTDEC	30
#define BREAKABLEOFFDEC	33


//around offsets
#define UP_OFF		0
#define UPRIGHT_OFF	1
#define RIGHT_OFF	2
#define DOWNRIGHT_OFF	3
#define DOWN_OFF	4
#define DOWNLEFT_OFF	5
#define LEFT_OFF	6
#define UPLEFT_OFF	7

typedef struct aroundCases
{
  unsigned long	long mask;
  int	decal;
  int	x;
  int	y;
  unsigned long	long opposite;
  int		opp_decal;
  int	off;
  int	opp_off;
}	aroundCases;

typedef struct pos
{
  int	x;
  int	y;
}	pos;

typedef struct freeThree
{
  pos	cases[3];
}	freeThree;

class SFMLCanvas;

class Game
{
  unsigned long long _board[Y_SIZE][X_SIZE];
  bool		_playing;
  Player	*_players[2];
  int		_turn;
  bool		_breakableFive;
  bool		_doubleThreeFree;
  Player	*_winner;
  SFMLCanvas    *_sfml;

  unsigned long	long	getValue(int const& ,int const& ,unsigned long long  const&, int const&) const;
  void		changeValue(int const&, int const&, unsigned long long const&, int const&, unsigned long long const&);
  void		changeAround(int const&, int const&, int const&);
  void		changeAligns(int const&, int const&);
  void		changeAlignsAround(int const&, int const&, unsigned long long const&, int const&, int const&, aroundCases const&);
  void		changeFiveRow(int const&, int const&);
  void		checkBreakable(int const&, int const&);
  bool		checkCase(int const&, int const&);
  void		changeBreakable(int const&, int const&);
  void		affectBreakable(int const&, int const&, Player*);
  void		deleteCase(int const&, int const&);
  bool		checkBreakableFive(int const&, int const&);
  void		checkEnd();
  bool		checkdoubleThree(int const&, int const&, unsigned long long const&);
  std::list<freeThree>	getfreeThreeList(int const&, int const&);
  bool		checkdoubleInList(std::list<freeThree>&);
  void		printBoard();
public:
  explicit Game(Player*, Player*, bool, bool, SFMLCanvas *sfml);
  virtual ~Game() {}

  void	printBoard() const;
  std::string	play(unsigned int x, unsigned int y);
};
