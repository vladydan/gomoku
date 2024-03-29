#include <cstring>
#include <fstream>
#include <tgmath.h>
#include "Pattern.hpp"
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

std::map<const std::string, Pattern> patternsMap;

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

void    Game::initPatternsMap() {
    std::ifstream file(PATTERNS_FILE);
    std::string pat;
    std::string score;
    std::string avScore;

    while (file.good()) {
        std::getline(file, pat, ';');
        std::getline(file, score, ';');
        std::getline(file, avScore);
        Pattern newPat;
        newPat.setPattern(pat);
        newPat.setScore(std::stoi(score));
        newPat.setAverageScore(std::stoi(avScore));
        patternsMap.insert(std::pair<std::string, Pattern>(pat, newPat));
    }
    file.close();
}

bool        Game::getIA() const {
    return (_players[0]->getType() == Player::IA || _players[1]->getType() == Player::IA);
}

int         Game::getScore(unsigned long long *board, int const &color, int const &broke) {
/*    if (!checkEnd(board, false, color))
        return (10000000);*/
    std::vector<Pattern> patterns = findPatterns(board, color, broke);
    int score = 0;

    for (std::vector<Pattern>::iterator it = patterns.begin() ; it != patterns.end() ; it++) {
        score += it->getScore();
    }
    return (score);
}

int         Game::getTotalScore(unsigned long long *board, int const &color, int const &broke1, int const &broke2) {
    if (color == BLACK)
        return ((getScore(board, BLACK, broke1) * ((broke2 - broke1) + 1)) - (getScore(board, WHITE, broke2) * ((broke1 - broke2) + 1)));
    else
        return ((getScore(board, WHITE, broke1) * ((broke2 -broke1) + 1)) - (getScore(board, BLACK, broke2) * ((broke1 - broke2) + 1)));
}

int         Game::getPatternScore(std::string const &pat, bool TwoD, int const &broke)
{
    if (pat == "oxx-" || pat == "-xxo") {
        return ((int) (- pow(10, (broke / 2) + 1)));
    }
    if (TwoD) {
        return((int) pow(10, (round(std::count(pat.begin(), pat.end(), 'x') / 2)) + 1));
    }
    else {
        return ((int) pow(10, std::count(pat.begin(), pat.end(), 'x')));
    }
}

std::vector<Pattern>  Game::find2DPatterns(std::vector<Pattern> &patterns, int const &broke) {
    std::vector<Pattern> donePat;
    std::vector<Pattern> toAdd;
    int x1;
    int x2;
    int y1;
    int y2;
    for (std::vector<Pattern>::iterator it = patterns.begin(); it != patterns.end(); it++) {
        for (int i = 0; i < (int) it->getPattern().size(); i++) {
            for (std::vector<Pattern>::iterator it2 = patterns.begin(); it2 != patterns.end(); it2++) {
                if (*it != *it2 && std::find(donePat.begin(), donePat.end(), *it2) == donePat.end() &&
                    it2->getDirection() != it->getDirection() &&
                    it2->getDirection() != around[it->getDirection()].opp_off) {
                    for (int j = 0; j < (int) it2->getPattern().size(); j++) {
                        x1 = it->getX() + (i * around[it->getDirection()].x);
                        y1 = it->getY() + (i * around[it->getDirection()].y);
                        x2 = it2->getX() + (j * around[it2->getDirection()].x);
                        y2 = it2->getY() + (j * around[it2->getDirection()].y);
                        if (x1 == x2 && y1 == y2) {
                            Pattern newPat;
                            newPat.setPattern(
                                    it->getPattern() + std::to_string(i) + std::to_string(j) + it2->getPattern());
                            newPat.setScore(getPatternScore(newPat.getPattern(), true, broke));
                            newPat.setAverageScore(getPatternScore(newPat.getPattern(), true, broke));
                            newPat.setX(it->getX());
                            newPat.setY(it->getY());
                            if (patternsMap.find(newPat.getPattern()) != patternsMap.end()) {
                                newPat.setScore(patternsMap[newPat.getPattern()].getScore());
                                newPat.setAverageScore(patternsMap[newPat.getPattern()].getAverageScore());
                            }
                            toAdd.push_back(newPat);
                        }
                    }
                }
            }
        }
        donePat.push_back(*it);
    }
    for (std::vector<Pattern>::iterator it = toAdd.begin(); it != toAdd.end(); it++)
        patterns.push_back(*it);
    return (patterns);
}

std::vector<Pattern> Game::findPatterns(unsigned long long *board, int const &color, int const& broke) {
    int x;
    int y;
    int x_save;
    int y_save;
    int n_save;
    int spaces;
    int tempX;
    int tempY;
    std::vector<Pattern> found;

    int n = 0;
    while (n < TABLESIZE) {
        x = TO_X(n);
        y = TO_Y(n);
        if ((board[COORD(x, y)] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) {
            n_save = n;
            for (int i = 0 ; i < 4 ; ++i) {
                std::string pat = "";
                x_save = x;
                y_save = y;
                spaces = 0;
                for (int j = 0; j < 5; ++j) {
                    if (checkCase(x, y)) {
                        if ((board[COORD(x, y)] & EMPTYMASK) == 0) {
                            pat += "-";
                            spaces += 1;
                        } else {
                            if ((board[COORD(x, y)] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) {
                                pat += "x";
                            } else {
                                pat += "o";
                                break;
                            }
                            spaces = 0;
                        }
                        x += around[i].x;
                        y += around[i].y;
                        if (spaces >= 3) {
                            x = x_save;
                            y = y_save;
                            break;
                        }
                    } else {
                        break;
                    }
                    tempX = x_save + around[around[i].opp_off].x;
                    tempY = y_save + around[around[i].opp_off].y;
                    if ((pat.find("xxo") != std::string::npos &&
                         checkCase(tempX, tempY) &&
                         ((board[COORD(tempX, tempY)] & EMPTYMASK) == 0)) ||
                        (pat.find("xx-") != std::string::npos &&
                         checkCase(tempX, tempY) &&
                         ((board[COORD(tempX, tempY)] & EMPTYMASK) == 1) &&
                         ((board[COORD(tempX, tempY)] & COLORMASK) ==
                          OPPOSITECOLOR(color)))) {
                        break;
                    }
                }
                tempX = x_save + around[around[i].opp_off].x;
                tempY = y_save + around[around[i].opp_off].y;
                if (checkCase(tempX, tempY) &&
                    ((board[COORD(tempX, tempY)] &
                      COLOREMPTYMASK) == COLORMASKCUSTOM(color))) {
                }
                else {
                    Pattern newPat;
                    if (checkCase(tempX, tempY)) {
                        if ((board[COORD(tempX, tempY)] & EMPTYMASK) == 0) {
                            pat.insert(0, "-");
                            x_save = tempX;
                            y_save = tempY;
                        } else if ((board[COORD(tempX, tempY)] & COLOREMPTYMASK) ==
                                   COLORMASKCUSTOM(OPPOSITECOLOR(color))) {
                            pat.insert(0, "o");
                            x_save = tempX;
                            y_save = tempY;
                        }
                    }
                    if (std::count(pat.begin(), pat.end(), 'x') >= 2 && std::count(pat.begin(), pat.end(), 'o') <= 1) {
                        std::string reverse(pat);
                        std::reverse(reverse.begin(), reverse.end());
                        if (patternsMap.find(pat) != patternsMap.end()) {
                            newPat.setPattern(pat);
                            newPat.setScore(patternsMap[pat].getScore());
                            newPat.setAverageScore(patternsMap[pat].getAverageScore());
                            newPat.setX(x_save);
                            newPat.setY(y_save);
                            newPat.setDirection(i);
                        } else if (patternsMap.find(reverse) != patternsMap.end()) {
                            newPat.setPattern(reverse);
                            newPat.setScore(patternsMap[reverse].getScore());
                            newPat.setAverageScore(patternsMap[reverse].getAverageScore());
                            newPat.setX(x_save + ((int) reverse.size() - 1) * around[i].x);
                            newPat.setY(y_save + ((int) reverse.size() - 1) * around[i].y);
                            newPat.setDirection(around[i].opp_off);
                        } else {
                            newPat.setPattern(pat);
                            newPat.setScore(getPatternScore(pat, false, broke));
                            newPat.setAverageScore(getPatternScore(pat, false, broke));
                            newPat.setX(x_save);
                            newPat.setY(y_save);
                            newPat.setDirection(i);
                        }
                        found.push_back(newPat);
                    }
                }
/*                if (x_save > x)
                    x = x_save;
                if (y_save > y)
                    y = y_save;*/
                x = TO_X(n_save);
                y = TO_Y(n_save);
            }
            n = n_save;
        }
        ++n;
    }
    return (found);
//    return (find2DPatterns(found, broke));
}

void    Game::setBreakableFive(bool state)
{
  this->_breakableFive = state;
}

void    Game::setDoubleThreeFree(bool state)
{
  this->_doubleThreeFree = state;
}

unsigned long long	Game::getValue(unsigned long long *board, int const& x, int const& y, unsigned long long const& mask, int const& decal) {
    if (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE)
        return ((board[COORD(x, y)] & mask) >> decal);
    return (0);
}

void	Game::changeValue(unsigned long long *board, int const& x, int const& y, unsigned long long const& mask, int const& decal, unsigned long long const& value) {
    if (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE) {
        board[COORD(x, y)] &= ~mask;
        board[COORD(x, y)] |= value << decal;
    }
}

void	Game::printBoard(unsigned long long *board) {
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
//            std::cout << board[COORD(x,y)] << " ";
            if ((board[COORD(x, y)] & EMPTYMASK) == 0)
                std::cout << '.';
            else
                std::cout << ((board[COORD(x, y)] & COLORMASK) >> 1) ;
        }
        std::cout << std::endl;
    }
}

std::list<freeThree>	Game::getfreeThreeList(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    unsigned long long color = ((board[COORD(x,y)] & COLORMASK) >> 1);
    std::list<freeThree> list;

    while (around[i].mask != 0) {
        if (checkCase(x + 3 * around[i].x, y + 3 * around[i].y) &&
            checkCase(x + around[around[i].opp_off].x, y + around[around[i].opp_off].y) &&
            getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) == 0 &&
            getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
            getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color &&
            getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
            getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
            getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) == 0) {
            freeThree var;
            var.cases[0] = {x, y};
            var.cases[1] = {x + around[i].x, y + around[i].y};
            var.cases[2] = {x + 2 * around[i].x, y + 2 * around[i].y};
            list.push_back(var);
        } else if (checkCase(x + 2 * around[i].x, y + 2 * around[i].y) &&
                   checkCase(x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y) &&
                   getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) == 0 &&
                   getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
                   getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color &&
                   getValue(board, x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y, EMPTYMASK,
                            0) == 0 &&
                   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) !=
                   0 &&
                   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) ==
                   color) {
            freeThree var;
            var.cases[0] = {x + around[i].x, y + around[i].y};
            var.cases[1] = {x, y};
            var.cases[2] = {x + around[around[i].opp_off].x, y + around[around[i].opp_off].y};
            list.push_back(var);
        } else if (checkCase(x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y) &&
                   checkCase(x + 3 * around[i].x, y + 3 * around[i].y) &&
                   getValue(board, x + 2 * around[around[i].opp_off].x, y + 2 * around[around[i].opp_off].y, EMPTYMASK,
                            0) == 0 &&
                   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) !=
                   0 &&
                   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) ==
                   color &&
                   getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0 &&
                   getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
                   getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
                   getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) == 0) {
            freeThree var;
            var.cases[0] = {x + around[around[i].opp_off].x, y + around[around[i].opp_off].y};
            var.cases[1] = {x, y};
            var.cases[2] = {x + 2 * around[i].x, y + 2 * around[i].y};
            list.push_back(var);
        } else if (checkCase(x + 4 * around[i].x, y + 4 * around[i].y) &&
                   checkCase(x + around[around[i].opp_off].x, y + around[around[i].opp_off].y) &&
                   getValue(board, x + 4 * around[i].x, y + 4 * around[i].y, EMPTYMASK, 0) == 0 &&
                   getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, EMPTYMASK, 0) != 0 &&
                   getValue(board, x + 3 * around[i].x, y + 3 * around[i].y, COLORMASK, 1) == color &&
                   getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) ==
                   0) {
            if (getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) == 0 &&
                getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
                getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color) {
                freeThree var;
                var.cases[0] = {x, y};
                var.cases[1] = {x + around[i].x, y + around[i].y};
                var.cases[2] = {x + 3 * around[i].x, y + 3 * around[i].y};
                list.push_back(var);
            } else if (getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, EMPTYMASK, 0) != 0 &&
                       getValue(board, x + 2 * around[i].x, y + 2 * around[i].y, COLORMASK, 1) == color &&
                       getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0) {
                freeThree var;
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

bool	Game::checkdoubleInList(std::list<freeThree> & list) {
    std::list<pos> cases;

    for (std::list<freeThree>::iterator it = list.begin(); it != list.end(); it++) {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (std::list<pos>::iterator itc = cases.begin(); itc != cases.end(); itc++) {
                if (it->cases[i].x == itc->x && it->cases[i].y == itc->y)
                    count += 1;
            }
        }
        if (count == 1)
            return (true);
        for (int i = 0; i < 3; i++) {
            bool to_push = true;
            for (std::list<pos>::iterator itc = cases.begin(); itc != cases.end(); itc++) {
                if (it->cases[i].x == itc->x && it->cases[i].y == itc->y)
                    to_push = false;
            }
            if (to_push)
                cases.push_back(it->cases[i]);
        }
    }
    return (false);
}

bool	Game::checkdoubleThree(unsigned long long *board, int const& x, int const& y, unsigned long long const& color) {
    std::list<freeThree> list;

    changeValue(board, x, y, COLORMASK, 1, color);
    changeValue(board, x, y, EMPTYMASK, 0, 1);
    list = getfreeThreeList(board, x, y);
    if (!checkdoubleInList(list)) {
        for (std::list<freeThree>::iterator it = list.begin(); it != list.end(); it++) {
            for (int i = 0; i < 3; i++) {
                if (it->cases[i].x != x || it->cases[i].y != y) {
                    std::list<freeThree> l = getfreeThreeList(board, it->cases[i].x, it->cases[i].y);
                    if (checkdoubleInList(l)) {
                        std::cout << "double trois : " << it->cases[i].x << " " << it->cases[i].y << std::endl;
                        changeValue(board, x, y, COLORMASK, 1, 0);
                        changeValue(board, x, y, EMPTYMASK, 0, 0);
                        return (true);
                    }
                }
            }
        }
    } else {
        std::cout << "double trois : " << x << " " << y << std::endl;
        changeValue(board, x, y, COLORMASK, 1, 0);
        changeValue(board, x, y, EMPTYMASK, 0, 0);
        return (true);
    }
    changeValue(board, x, y, COLORMASK, 1, 0);
    changeValue(board, x, y, EMPTYMASK, 0, 0);
    return (false);
}

bool	Game::checkBreakableFive(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    bool broke;

    if ((board[COORD(x, y)] & BREAKABLE) != 0)
        return (true);
    while (i < 4) {
        broke = false;
        int sideOne = (int) ((board[COORD(x, y)] & around[i].mask) >> around[i].decal);
        int sideTwo = (int) ((board[COORD(x, y)] & around[i].opposite) >> around[i].opp_decal);
//        int sideOne = (int) getValue(board, x, y, around[i].mask, around[i].decal);
//        int sideTwo = (int) getValue(board, x, y, around[i].opposite, around[i].opp_decal);
        if ((sideOne + sideTwo + 1) >= 5) {
            int m;
            for (m = 0; m < sideOne; m++) {
                if (((board[COORD((x + (m + 1) * around[i].x), (y + (m + 1) * around[i].y))] & BREAKABLE) >> BREAKABLEDEC) != 0) {
//                if (getValue(board, x + (m + 1) * (around[i].x), y + (m + 1) * (around[i].y), BREAKABLE,
//                             BREAKABLEDEC) != 0) {
                    broke = true;
                    break;
                }
            }
            int n;
            for (n = 0; n < sideTwo; n++) {
                if (((board[COORD((x + (n+1) * around[around[i].opp_off].x), (y + (n+1) * around[around[i].opp_off].y))] & BREAKABLE) >> BREAKABLEDEC) != 0) {
//                if (getValue(board, x + (n + 1) * (around[around[i].opp_off].x),
//                             y + (n + 1) * (around[around[i].opp_off].y), BREAKABLE, BREAKABLEDEC) != 0) {
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


bool	Game::checkEnd(unsigned long long *board, bool breakableFive, int const &color) {
/*  for (int i = 0 ; i < 2 ; i++)
    {
      if (_players[i]->getBroke() >= 10)
	{
	  _playing = false;
	  _winner = _players[i];
	  return;
	}
    }*/
    for (int i = 0; i < TABLESIZE; i++) {
        if ((board[i] & FIVEROW) != 0 &&
                ((board[i] & COLOREMPTYMASK) == COLORMASKCUSTOM(color) &&
                        (!breakableFive || !checkBreakableFive(board, TO_X(i), TO_Y(i)))))
            return (false);
    }
/*  for (int y = 0; y < Y_SIZE ; ++y) {
      for (int x = 0; x < X_SIZE; ++x) {
          if ((board[COORD(x, y)] & FIVEROW) != 0 && (!breakableFive || !checkBreakableFive(board, x, y)))
              return (false);
      }
  }*/
    return (true);
}

bool	Game::checkCase(int const& x, int const& y) {
    return (x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE);
}

void	Game::deleteCase(unsigned long long *board, int const& x, int const& y, SFMLCanvas *sfml) {
    int i = 0;
    unsigned long long color = ((board[COORD(x, y)] & COLORMASK) >> 1);
//    unsigned long long color = getValue(board, x, y, COLORMASK, 1);
    unsigned long long ar = ((board[COORD(x, y)] & DOUBLEZONE) >> ZONEDEC);
//    unsigned long long ar = getValue(board, x, y, AROUND, AROUNDDEC);

    changeAround(board, x, y);
    board[COORD(x, y)] = 0;
    if (sfml)
        sfml->removePiece(x, y);
    changeValue(board, x, y, DOUBLEZONE, ZONEDEC, ar);
    changeAligns(board, x, y);
    while (around[i].mask != 0) {
        changeAligns(board, x + around[i].x, y + around[i].y);
        if ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) {
//        if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//            getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color) {
            changeBreakable(board, x + around[i].x, y + around[i].y);
        } else if ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(OPPOSITECOLOR(color))) {
//        } else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0) {
            checkBreakable(board, x + around[i].x, y + around[i].y);
            checkBreakable(board, x + 2 * around[i].x, y + 2 * around[i].y);
        }
        ++i;
    }
}

void	Game::affectBreakable(unsigned long long *board, int const& x, int const& y, Player *player, int i, SFMLCanvas *sfml) {
    unsigned long long color = ((board[COORD(x, y)] & COLORMASK) >> 1);
//    unsigned long long color = getValue(board, x, y, COLORMASK, 1);

    while (around[i].mask != 0) {
        if (checkCase(x + around[i].x, y + around[i].y) &&
                (((board[COORD((x + around[i].x), (y + around[i].y))] & BREAKABLE_OFF) >> BREAKABLEOFFDEC) & (1 << around[i].opp_off)) != 0) {
//            (getValue(board, x + around[i].x, y + around[i].y, BREAKABLE_OFF, BREAKABLEOFFDEC) &
//             (1 << around[i].opp_off)) != 0) {
            if ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) {
//            if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//                getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color) {
                checkBreakable(board, x + around[i].x, y + around[i].y);
                checkBreakable(board, x + 2 * (around[i].x), y + 2 * (around[i].y));
            } else if ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(OPPOSITECOLOR(color))) {
//            } else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0) {
                affectBreakable(board, x, y, player, i + 1, sfml);
                deleteCase(board, x + around[i].x, y + around[i].y, sfml);
                deleteCase(board, x + 2 * (around[i].x), y + 2 * (around[i].y), sfml);
                player->setBroke(player->getBroke() + 2);
            }
        }
        ++i;
    }
}

void	Game::checkBreakable(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    unsigned long long color = ((board[COORD(x, y)] & COLORMASK) >> 1);
//    unsigned long long color = getValue(board, x, y, COLORMASK, 1);
    bool breakable = false;

    changeValue(board, x, y, BREAKABLE_OFF, BREAKABLEOFFDEC, 0); // reinit le breakableoff
    while (around[i].mask != 0) {
        if (checkCase(x + around[i].x, y + around[i].y) &&
            checkCase(x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y))) {
            if ((board[COORD((x + around[i].x), (y + around[i].y))] & EMPTYMASK) == 0 &&
                    ((board[COORD((x + around[around[i].opp_off].x), (y + around[around[i].opp_off].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) &&
                    ((board[COORD((x + 2 * around[around[i].opp_off].x), (y + 2 * around[around[i].opp_off].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(OPPOSITECOLOR(color)))) {
//            if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) == 0 &&
//                getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK, 0) != 0 &&
//                getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK, 1) ==
//                color &&
//                getValue(board, x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y), EMPTYMASK,
//                         0) != 0 &&
//                getValue(board, x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y), COLORMASK,
//                         1) != color) {
                changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 1);
                changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, BREAKABLE,
                            BREAKABLEDEC, 1);
                changeValue(board, x, y, ((unsigned long long) 1 << (BREAKABLEOFFDEC + i)), BREAKABLEOFFDEC + i, 1);
                changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y,
                            ((unsigned long long) 1 << (BREAKABLEOFFDEC + i)), BREAKABLEOFFDEC + i, 1);
                breakable = true;
            } else if ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(OPPOSITECOLOR(color)) &&
                    ((board[COORD((x + around[around[i].opp_off].x), (y + around[around[i].opp_off].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color)) &&
                    ((board[COORD((x + 2 * around[around[i].opp_off].x), (y + 2 * around[around[i].opp_off].y))] & EMPTYMASK) == 0)) {
//            } else if (getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//                       getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) != color &&
//                       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, EMPTYMASK,
//                                0) != 0 &&
//                       getValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, COLORMASK,
//                                1) == color &&
//                       getValue(board, x + 2 * (around[around[i].opp_off].x), y + 2 * (around[around[i].opp_off].y),
//                                EMPTYMASK, 0) == 0) {
                changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 1);
                changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y, BREAKABLE,
                            BREAKABLEDEC, 1);
                changeValue(board, x, y, ((unsigned long long) 1 << (BREAKABLEOFFDEC + around[i].opp_off)),
                            BREAKABLEOFFDEC + around[i].opp_off, 1);
                changeValue(board, x + around[around[i].opp_off].x, y + around[around[i].opp_off].y,
                            ((unsigned long long) 1 << (BREAKABLEOFFDEC + around[i].opp_off)),
                            BREAKABLEOFFDEC + around[i].opp_off, 1);
                breakable = true;
            }
        }
        ++i;
    }
    if (!breakable)
        changeValue(board, x, y, BREAKABLE, BREAKABLEDEC, 0);
}

void	Game::changeBreakable(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    unsigned long long color = ((board[COORD(x, y)] & COLORMASK) >> 1);
//    unsigned long long color = getValue(board, x, y, COLORMASK, 1);

    while (around[i].mask != 0) {
        if (checkCase(x + around[i].x, y + around[i].y) &&
                ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(OPPOSITECOLOR(color)))) {
//            getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//            getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) != color)
            checkBreakable(board, x + around[i].x, y + around[i].y);
        }
        ++i;
    }
    checkBreakable(board, x, y);
}

void	Game::changeFiveRow(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    unsigned long long value;

    while (around[i].mask != 0) {
        value = ((board[COORD(x, y)] & around[i].mask) >> around[i].decal) + ((board[COORD(x, y)] & around[i].opposite) >> around[i].opp_decal) + 1;
//        value = getValue(board, x, y, around[i].mask, around[i].decal) + getValue(board, x, y, around[i].opposite, around[i].opp_decal) + 1;
        if (value >= 5) {
            changeValue(board, x, y, FIVEROW, FIVEROWDEC, 1);
            return;
        }
        ++i;
    }
    changeValue(board, x, y, FIVEROW, FIVEROWDEC, 0);
}

void	Game::changeAlignsAround(unsigned long long *board, int const& x, int const& y, unsigned long long const& color, int const& opp_x, int const& opp_y, aroundCases const& direction) {
    if (x < 0 || x >= X_SIZE || y < 0 || y >= Y_SIZE)
        return;
    unsigned long long value;
    if ((board[COORD(opp_x, opp_y)] & EMPTYMASK) != 0) {
        value = ((board[COORD(opp_x, opp_y)] & direction.opposite) >> direction.opp_decal) + 1;
        //value = getValue(board, opp_x, opp_y, direction.opposite, direction.opp_decal) + 1;
    }
    else {
        value = 0;
    }

    changeValue(board, x, y, direction.opposite, direction.opp_decal, value);
    changeFiveRow(board, x, y);
    if (checkCase(x + direction.x, y + direction.y) &&
            ((board[COORD((x + direction.x), (y + direction.y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color))) {
//        getValue(board, x + direction.x, y + direction.y, EMPTYMASK, 0) != 0 &&
//        getValue(board, x + direction.x, y + direction.y, COLORMASK, 1) == color)
        changeAlignsAround(board, x + direction.x, y + direction.y, color, x, y, direction);
    }
}

void	Game::changeAligns(unsigned long long *board, int const& x, int const& y) {
    int i = 0;
    unsigned long long value;
    unsigned long long color = ((board[COORD(x, y)] & COLORMASK) >> 1);
//    unsigned long long color = getValue(board, x, y, COLORMASK, 1);

    if ((board[COORD(x, y)] & EMPTYMASK) != 0) {
//    if (getValue(board, x, y, EMPTYMASK, 0) != 0) {
        while (around[i].mask != 0) {
            if (checkCase(x + around[i].x, y + around[i].y) &&
                    ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color))) {
//                getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//                getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color) {
                value = ((board[COORD((x + around[i].x), (y + around[i].y))] & around[i].mask) >> around[i].decal) + 1;
//                value = getValue(board, x + around[i].x, y + around[i].y, around[i].mask, around[i].decal) + 1;
                changeValue(board, x, y, around[i].mask, around[i].decal, value);
            }
            ++i;
        }
        i = 0;
        while (around[i].mask != 0) {
            if (checkCase(x + around[i].x, y + around[i].y) &&
                    ((board[COORD((x + around[i].x), (y + around[i].y))] & COLOREMPTYMASK) == COLORMASKCUSTOM(color))) {
//                getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0 &&
//                getValue(board, x + around[i].x, y + around[i].y, COLORMASK, 1) == color)
                changeAlignsAround(board, x + around[i].x, y + around[i].y, color, x, y, around[i]);
            }
            ++i;
        }
        changeFiveRow(board, x, y);
    } else {
        while (around[i].mask != 0) {
            if (checkCase(x + around[i].x, y + around[i].y) &&
                    ((board[COORD((x + around[i].x), (y + around[i].y))] & EMPTYMASK) != 0)) {
//                getValue(board, x + around[i].x, y + around[i].y, EMPTYMASK, 0) != 0)
                changeAlignsAround(board, x + around[i].x, y + around[i].y, ((board[COORD(x + around[i].x, y + around[i].y)] & COLORMASK) >> 1), x, y, around[i]);
            }
            ++i;
        }
    }
}

void	Game::changeAround(unsigned long long *board, int const& x, int const& y) {
    int i = 0;

    changeValue(board, x, y, ZONECLOSE, ZONECLOSEDEC, 1);
    changeValue(board, x, y, ZONE, ZONEDEC, 1);
    while (around[i].mask != 0) {
        if (checkCase(x + around[i].x, y + around[i].y)) {
            changeValue(board, x + around[i].x, y + around[i].y, ZONE, ZONEDEC, 1);
            changeValue(board, x + around[i].x, y + around[i].y, ZONECLOSE, ZONECLOSEDEC, 1);
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

Player::PlayerType Game::getCurrentPlayerType() const
{
  return _players[_turn % 2]->getType();
}

void Game::playIa()
{
    int x = 0;
    int y = 0;
    std::vector<coords> coordinates;
    int color;

    color = _players[_turn % 2]->getColor();
//    std::cout << color << std::endl;
    coordinates = MinMax::algo(_board, *(_players[_turn % 2]), *(_players[(_turn + 1) % 2]), _breakableFive);
    for (coords c : coordinates) {
        if (!_doubleThreeFree || !checkdoubleThree(_board, c.x, c.y, color)) {
            x = c.x;
            y = c.y;
            break;
        }
    }
    _sfml->iaFinish();
    _sfml->trySetPiece(x,y);
}

void        Game::changePatternFile() const {
    for (int i = 0; i < 2; i++) {
        for (const Pattern &p : _players[i]->getPatterns()) {
            if (patternsMap.find(p.getPattern()) == patternsMap.end() && p.getPattern() != "oxx-" &&
                p.getPattern() != "-xxo")
                patternsMap.insert(std::pair<std::string, Pattern>(p.getPattern(), p));
        }
    }
    for (int i = 0; i < 2; i++) {
        for (const Pattern &p : _players[i]->getPatterns()) {
            if (_players[i] == _winner)
                patternsMap[p.getPattern()].setScore(std::min(patternsMap[p.getPattern()].getScore() + 3,
                                                              patternsMap[p.getPattern()].getAverageScore() + 100));
            else
                patternsMap[p.getPattern()].setScore(std::max(patternsMap[p.getPattern()].getScore() - 1,
                                                              patternsMap[p.getPattern()].getAverageScore() - 100));
        }
    }
    std::ofstream newFile(PATTERNS_FILE);
    if (newFile.is_open()) {
        for (std::pair<const std::string, Pattern> &p : patternsMap) {
            if (p.second.getPattern() != "")
                newFile << p.second.getPattern() << ";" << p.second.getScore() << ";" << p.second.getAverageScore()
                        << std::endl;
        }
    }
    newFile.close();
}

void		Game::playTerminal() {
    int x;
    int y;
    int color;
    std::vector<Pattern> found;
    std::vector<coords> coordinates;

    initPatternsMap();
    while (_playing) {
        printBoard(_board);
        color = _players[_turn % 2]->getColor();
        if (_players[_turn % 2]->getType() == Player::IA) {
            coordinates = MinMax::algo(_board, *(_players[_turn % 2]), *(_players[(_turn + 1) % 2]), _breakableFive);
            for (coords c : coordinates) {
                if (!_doubleThreeFree || !checkdoubleThree(_board, c.x, c.y, color)) {
                    x = c.x;
                    y = c.y;
                    break;
                }
            }
        } else {
            std::cin >> x;
            std::cin >> y;
        }
        if ((_board[COORD(x, y)] & EMPTYMASK) == 0 && (!_doubleThreeFree || !checkdoubleThree(_board, x, y, color))) {
            changeValue(_board, x, y, COLORMASK, 1, color);
            changeValue(_board, x, y, EMPTYMASK, 0, 1);
            changeAround(_board, x, y);
            changeAligns(_board, x, y);
            affectBreakable(_board, x, y, _players[_turn % 2], 0, NULL);
            changeBreakable(_board, x, y);
            _playing = (checkEnd(_board, _breakableFive, BLACK) && checkEnd(_board, _breakableFive, WHITE));
            found = findPatterns(_board, color, _players[(_turn + 1) % 2]->getBroke());
            for (std::vector<Pattern>::iterator it = found.begin(); it != found.end(); it++) {
                std::cout << "Pattern : " << it->getPattern() << " score : " << it->getScore() << " " << it->getX() << " "
                          << it->getY() << std::endl;
                _players[_turn % 2]->addPattern(*it);
            }
            if (_playing && _players[0]->getBroke() < 10 && _players[1]->getBroke() < 10)
                _turn++;
            else {
                if (_winner == NULL)
                    _winner = _players[_turn % 2];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (const Pattern &p : _players[i]->getPatterns()) {
            if (patternsMap.find(p.getPattern()) == patternsMap.end() && p.getPattern() != "oxx-" &&
                p.getPattern() != "-xxo")
                patternsMap.insert(std::pair<std::string, Pattern>(p.getPattern(), p));
        }
    }
    for (int i = 0; i < 2; i++) {
        for (const Pattern &p : _players[i]->getPatterns()) {
            if (_players[i] == _winner)
                patternsMap[p.getPattern()].setScore(std::min(patternsMap[p.getPattern()].getScore() + 3,
                                                              patternsMap[p.getPattern()].getAverageScore() + 100));
            else
                patternsMap[p.getPattern()].setScore(std::max(patternsMap[p.getPattern()].getScore() - 1,
                                                              patternsMap[p.getPattern()].getAverageScore() - 100));
        }
    }
    changePatternFile();
    printBoard(_board);
    std::cout << "Player : " << _winner->getName() << " wins!" << std::endl;
}

std::string	Game::play(unsigned int x, unsigned int y) {
    int color;

    color = _players[_turn % 2]->getColor();
    if ((_board[COORD(x, y)] & EMPTYMASK) == 0 && (!_doubleThreeFree || !checkdoubleThree(_board, x, y, color))) {
        std::cout << x << " " << y << std::endl;
        changeValue(_board, x, y, COLORMASK, 1, color);
        changeValue(_board, x, y, EMPTYMASK, 0, 1);
        changeAround(_board, x, y);
        changeAligns(_board, x, y);
        affectBreakable(_board, x, y, _players[_turn % 2], 0, _sfml);
        changeBreakable(_board, x, y);
        _playing = (checkEnd(_board, _breakableFive, BLACK) && checkEnd(_board, _breakableFive, WHITE));
        std::vector<Pattern> found = findPatterns(_board, color, _players[(_turn + 1) % 2]->getBroke());
        for (std::vector<Pattern>::iterator it = found.begin(); it != found.end(); it++) {
            if (std::find(_players[_turn % 2]->getPatterns().begin(), _players[_turn % 2]->getPatterns().end(), *it) == _players[_turn % 2]->getPatterns().end()) {
                _players[_turn % 2]->addPattern(*it);
            }
        }
//        std::cout << "Score : " << getScore(_board, _players[_turn %2]->getColor(), _players[(_turn + 1) % 2]->getBroke()) << std::endl;
        if (_playing && _players[0]->getBroke() < 10 && _players[1]->getBroke() < 10) {
            _turn++;
            _sfml->updateStat("Turn : " + std::to_string(_turn), "Black : " + std::to_string(_players[0]->getBroke()),
                              "White : " + std::to_string(_players[1]->getBroke()));
        } else {
            if (_winner == NULL)
                _winner = _players[_turn % 2];
            std::string winner = (_winner->getColor() == BLACK ? "black" : "white");
            _sfml->setWinner(winner);
        }
    } else {
        return ("null");
    }
    return (color == 0 ? "black" : "white");
}
