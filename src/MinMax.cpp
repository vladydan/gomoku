#include <omp.h>
#include <cstring>
#include "MinMax.hh"

std::vector<coords>     MinMax::algo(unsigned long long *board, Player playing, Player opponent, bool bF) {
    std::vector<coords> coord;
    coord.clear();
    for (int i = 0; i < TABLESIZE; i++) {
        if ((board[i] & ZONEEMPTY) == ZONE) {
            coords c;
            c.y = i / X_SIZE;
            c.x = i % X_SIZE;
            coord.push_back(c);
        }
    }

    if (coord.size() == 0) {
        coords c;
        c.x = 9;
        c.y = 9;
        coord.push_back(c);
        return (coord);
    }
    std::sort(coord.begin(), coord.end(),
            [&] (const coords &first, const coords &second) ->bool {
                return (((board[COORD(first.x, first.y)] & ZONECLOSE) >> ZONECLOSEDEC) > ((board[COORD(second.x, second.y)] & ZONECLOSE) >> ZONECLOSEDEC));
            });

#pragma omp parallel for num_threads(coord.size())
    for (int i = 0; i < (int) coord.size(); i++) {
        unsigned long long newBoard[TABLESIZE];

        memcpy(newBoard, board, sizeof(unsigned long long) * TABLESIZE);
        int x = coord[i].x;
        int y = coord[i].y;
        Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
        Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
        Game::changeAround(newBoard, x, y);
        Game::changeAligns(newBoard, x, y);
        Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
        Game::changeBreakable(newBoard, x, y);
        if (!Game::checkEnd(newBoard, bF, playing.getColor()) || playing.getBroke() >= 10) {
            coord[i].value = ((DEPTH + 1) * 100000000);
        } else {
            coord[i].value = MinMax::alphaBeta(newBoard, DEPTH, true, playing, opponent, -2147483648, 2147483647, bF);
        }
    }
    std::sort(coord.begin(), coord.end(),
              [](const coords &first, const coords &second) -> bool {
                  return first.value > second.value;
              });
/*    for (coords c : coord) {
        std::cout << c.x << " " << c.y << " " << c.value << std::endl;
    }*/
    return (coord);
}

long long		MinMax::alphaBeta(unsigned long long* board, short depth, bool maximisingPlayer, Player playing, Player opponent,
				  long long  alpha, long long beta, bool bF) {
    long long bestValue = 0;
    bool stop = false;

    if (maximisingPlayer)
        bestValue = alpha;
    else
        bestValue = beta;

    if (depth == DEPTH) {
        bestValue = alphaBeta(board, depth - 1, false, playing, opponent, alpha, beta, bF);
    } else {
        int color;
        if (maximisingPlayer) {
            color = opponent.getColor();
        }
        else {
            color = playing.getColor();
        }
        if (!Game::checkEnd(board, bF, color) || playing.getBroke() >= 10 || opponent.getBroke() >= 10) {
            if (playing.getBroke() >= 10) {
                return (((DEPTH + 1) * 100000000) / ((DEPTH - depth) + 1));
            }
            if (opponent.getBroke() >= 10) {
                return (-((DEPTH + 1) * 100000000) / ((DEPTH - depth) + 1));
            }
            if (!maximisingPlayer) {
                return (((DEPTH + 1) * 100000000) / ((DEPTH - depth) + 1));
            } else {
                return (-(((DEPTH + 1) * 100000000) / ((DEPTH - depth) + 1)));
            }
        }
        if (depth == 0) {
            bestValue = Game::getTotalScore(board, playing.getColor(), opponent.getBroke(), playing.getBroke());
            return (bestValue);
        }
        std::vector<coords> newCoordinates;
        for (int i = 0 ; i < TABLESIZE ; i++) {
            if ((board[i] & ZONEEMPTY) == ZONE) {
                coords c;
                c.y = i / X_SIZE;
                c.x = i % X_SIZE;
                newCoordinates.push_back(c);
            }
        }
        std::sort(newCoordinates.begin(), newCoordinates.end(),
                  [&] (const coords &first, const coords &second) ->bool {
                      return (((board[COORD(first.x, first.y)] & ZONECLOSE) >> ZONECLOSEDEC) > ((board[COORD(second.x, second.y)] & ZONECLOSE) >> ZONECLOSEDEC));
                  });

#pragma omp parallel for shared(bestValue, stop) num_threads(newCoordinates.size())
        for (int i = 0; i < (int) newCoordinates.size(); ++i) {
            if (!stop) {
                long long childValue = 0;
                unsigned long long newBoard[TABLESIZE];

                memcpy(newBoard, board, sizeof(unsigned long long) * TABLESIZE);

                int y = newCoordinates[i].y;
                int x = newCoordinates[i].x;
                if (!maximisingPlayer) {
                    Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
                    Game::changeValue(newBoard, x, y, COLORMASK, 1, opponent.getColor());
                    Game::changeAround(newBoard, x, y);
                    Game::changeAligns(newBoard, x, y);
                    Game::affectBreakable(newBoard, x, y, &opponent, 0, NULL);
                    Game::changeBreakable(newBoard, x, y);
                } else {
                    Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
                    Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
                    Game::changeAround(newBoard, x, y);
                    Game::changeAligns(newBoard, x, y);
                    Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
                    Game::changeBreakable(newBoard, x, y);
                }

                if (maximisingPlayer) {
                    childValue = alphaBeta(newBoard, depth - 1, false, playing, opponent, bestValue, beta,
                                           bF);

                    if (childValue < -50000000 && !stop && bestValue >= 50000000 && bestValue > abs(childValue)) {
                    }
                    else {
                        bestValue = std::max(bestValue, childValue);
                    }
                    if (beta <= bestValue)
                        stop = true;
                } else {
                    childValue = alphaBeta(newBoard, depth - 1, true, playing, opponent, alpha, bestValue,
                                           bF);
                    if (childValue > 50000000 && !stop && bestValue <= -50000000 && abs(bestValue) > childValue) {

                    }
                        else {
                        bestValue = std::min(bestValue, childValue);
                    }
                    if (bestValue <= alpha)
                        stop = true;
                }
            }
        }
    }

    return (bestValue);
}
