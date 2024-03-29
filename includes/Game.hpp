#pragma once

#include <map>
#include <iostream>
#include <algorithm>
#include <list>
#include <cmath>
#include <utility>
#include <thread>
#include "MinMax.hh"
#include "Pattern.hpp"
#include "Player.hpp"

#define X_SIZE 19
#define Y_SIZE 19
#define PATTERNS_FILE "patterns"
#define TABLESIZE 361

#define COORD(x, y)	(y * Y_SIZE + x)
#define TO_X(i) (i % Y_SIZE)
#define TO_Y(i) (i / Y_SIZE)

#define BLACK 0
#define WHITE 1

#define BLACKCASE 1
#define WHITECASE 3

#define COLORMASKCUSTOM(i) ((i == BLACK) ? (BLACKCASE) : (WHITECASE))
#define OPPOSITECOLOR(i) ((i == BLACK) ? (WHITE) : (BLACK))

//MASKS
#define EMPTYMASK	1 
#define COLORMASK	2 // 10
#define COLOREMPTYMASK 3 // 11
#define FIVEROW		4 // 100
#define BREAKABLE	8 // 1000
#define ZONE    	16 // 10000
#define ZONEEMPTY   17 // 10001
#define ZONECLOSE   32 // 100000
#define DOUBLEZONE  48 // 110000
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

//decal masks
#define FIVEROWDEC	2
#define BREAKABLEDEC	3
#define ZONEDEC	    4
#define ZONECLOSEDEC	5
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
  unsigned long long _board[Y_SIZE * X_SIZE];
  bool		_playing;
  Player	*_players[2];
  int		_turn;
  bool		_breakableFive;
  bool		_doubleThreeFree;
  Player	*_winner;
  SFMLCanvas    *_sfml;

    static void		changeAlignsAround(unsigned long long *board, int const&, int const&, unsigned long long const&, int const&, int const&, aroundCases const&);
    static void		changeFiveRow(unsigned long long *board, int const&, int const&);
    static void		checkBreakable(unsigned long long *board, int const&, int const&);
    static bool		checkCase(int const&, int const&);
    static void		deleteCase(unsigned long long *board, int const&, int const&, SFMLCanvas *sfml);
    static bool		checkBreakableFive(unsigned long long *board, int const&, int const&);
    static std::list<freeThree>	getfreeThreeList(unsigned long long *board, int const&, int const&);
    static bool		checkdoubleInList(std::list<freeThree>&);
    static int      getPatternScore(std::string const &, bool TwoD, int const &broke);
    static std::vector<Pattern> find2DPatterns(std::vector<Pattern> &patterns, int const &broke);
    static int      getScore(unsigned long long *board, int const &color, int const &broke);
public:
    explicit Game(Player*, Player*, bool, bool, SFMLCanvas *sfml);
    virtual ~Game() {}
    static unsigned long	long	getValue(unsigned long long *board, int const& ,int const& ,unsigned long long  const&, int const&);
    static void		changeValue(unsigned long long *board, int const&, int const&, unsigned long long const&, int const&, unsigned long long const&);
    static void		changeAround(unsigned long long *board, int const&, int const&);
    static void		changeAligns(unsigned long long *board, int const&, int const&);
    static void		changeBreakable(unsigned long long *board, int const&, int const&);
    static void		affectBreakable(unsigned long long *board, int const&, int const&, Player*, int, SFMLCanvas *sfml);
    static bool		checkEnd(unsigned long long *board, bool bF, int const &color);
    static bool		checkdoubleThree(unsigned long long *board, int const&, int const&, unsigned long long const&);
    static void     initPatternsMap();
    static std::vector<Pattern> findPatterns(unsigned long long *board, int const &color,int const& broke);
    static int      getTotalScore(unsigned long long *board, int const &color, int const &broke1, int const &broke2);
    void     changePatternFile() const;
    void    setBreakableFive(bool);
    void    setDoubleThreeFree(bool);
    bool    getIA() const;
    std::thread iaThread() {
      return std::thread(&Game::playIa, this);
    }
    Player::PlayerType getCurrentPlayerType() const;
    void playIa();
    int     getTurn() const;
    static void	printBoard(unsigned long long *board);
    void	playTerminal();
    std::string	play(unsigned int x, unsigned int y);
};
