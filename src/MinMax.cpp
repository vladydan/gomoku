#include <omp.h>
#include "MinMax.hh"

std::vector<coords>     MinMax::algo(unsigned long long *board, Player playing, Player opponent, bool bF) {
    std::vector<coords> coord;
    coord.clear();
    for (int i = 0 ; i < TABLESIZE ; i++) {
        if (Game::getValue(board, i % X_SIZE, i / X_SIZE, EMPTYMASK, 0) == 0 &&
            Game::getValue(board, i % X_SIZE, i / X_SIZE, ZONE, ZONEDEC) == 1) {
            coords c;
            c.y = i / X_SIZE;
            c.x = i % X_SIZE;
            coord.push_back(c);
        }
    }

    if (coord.size() == 0) {
        coords c;
        c.x = 10;
        c.y = 10;
        coord.push_back(c);
        return (coord);
    }
#pragma omp parallel for num_threads(coord.size())
    for (int i = 0 ; i < coord.size() ; i++) {
        unsigned long long newBoard[TABLESIZE];

        for (int n = 0 ; n < TABLESIZE ; n++)
            newBoard[n] = board[n];
        int x = coord[i].x;
        int y = coord[i].y;
        Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
        Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
        Game::changeAround(newBoard, x, y);
        Game::changeAligns(newBoard, x, y);
        Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
        Game::changeBreakable(newBoard, x, y);
        coord[i].value = MinMax::alphaBeta(newBoard, DEPTH, true, playing, opponent, -2147483648, 2147483647, bF);
    }
    std::sort(coord.begin(), coord.end(),
              [](const coords &first, const coords &second) -> bool {
                  return first.value > second.value;
              });
    for (coords c : coord) {
        std::cout << c.x << " " << c.y << " " << c.value << std::endl;
    }
    return (coord);
}

std::vector<coords>		MinMax::getNextMove(unsigned long long *board, Player playing, Player opponent) {
    std::vector<coords> coord;
    coord.clear();
    for (int y = 0; y < Y_SIZE; y++) {
        for (int x = 0; x < X_SIZE; x++) {
            if (Game::getValue(board, x, y, EMPTYMASK, 0) == 0 &&
                Game::getValue(board, x, y, ZONE, ZONEDEC) == 1) {
                coords c;
                c.y = y;
                c.x = x;
                coord.push_back(c);
            }
        }
    }
    if (coord.size() == 0) {
        coords c;
        c.x = 10;
        c.y = 10;
        coord.push_back(c);
        return (coord);
    }

    for (int i = 0, length = coord.size(); i < length; ++i)
        std::cout << coord.at(i).x << " " << coord.at(i).y << " " << coord.at(i).value << std::endl;
    #pragma omp parallel for
    for (int i = 0; i < coord.size(); ++i) {
        std::vector<coords> newCoords;
        unsigned long long newBoard[TABLESIZE];

        for (int n = 0; n < TABLESIZE; ++n)
            newBoard[n] = board[n];

        int y = coord[i].y;
        int x = coord[i].x;
        for (int n = 0; n < coord.size(); ++n) {
            if (n != i)
                newCoords.push_back(coord.at(n));
        }
        Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
        Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
        Game::changeAround(newBoard, x, y);
        Game::changeAligns(newBoard, x, y);
        Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
        Game::changeBreakable(newBoard, x, y);//ajouter une pierre noire a ces coordonnees
        coord[i].value = MinMax::alphaBeta(newBoard, DEPTH, true, playing, opponent, -2147483648, 2147483647,
                                           false);
    }

    std::sort(coord.begin(), coord.end(),
              [](const coords &first, const coords &second) -> bool {
                  return first.value > second.value;
              });
    return (coord);
}

int		MinMax::alphaBeta(unsigned long long* board, short depth, bool maximisingPlayer, Player playing, Player opponent,
				  int alpha, int beta, bool bF) {
    int bestValue = 0;
    bool stop = false;

    if (!Game::checkEnd(board, bF) || playing.getBroke() >= 10 || opponent.getBroke() >= 10) {
        if (playing.getBroke() >= 10) {
            return (((DEPTH + 1) * 10000000) / ((DEPTH - depth) + 1));
        } else if (opponent.getBroke() >= 10) {
            return (-((DEPTH + 1) * 10000000) / ((DEPTH - depth) + 1));
        }
        if ((!maximisingPlayer && DEPTH != depth) || (maximisingPlayer && DEPTH == depth)) {
            return (((DEPTH + 1) * 10000000) / ((DEPTH - depth) + 1));
        } else {
            return (-((DEPTH + 1) * 10000000) / ((DEPTH - depth) + 1));
        }
    }
    if (depth == 0) {
        bestValue = Game::getTotalScore(board, playing.getColor(), opponent.getBroke(), playing.getBroke());
        return (bestValue);
    }

    if (maximisingPlayer)
        bestValue = alpha;
    else
        bestValue = beta;

    if (depth == DEPTH) {
        bestValue = alphaBeta(board, depth - 1, false, playing, opponent, alpha, beta, bF);
    } else {
        std::vector<coords> newCoordinates;
        for (int i = 0 ; i < TABLESIZE ; i++) {
            if (Game::getValue(board, i % X_SIZE, i / X_SIZE, EMPTYMASK, 0) == 0 &&
                Game::getValue(board, i % X_SIZE, i / X_SIZE, ZONE, ZONEDEC) == 1) {
                coords c;
                c.y = i / X_SIZE;
                c.x = i % X_SIZE;
                newCoordinates.push_back(c);
            }
        }

#pragma omp parallel for shared(bestValue, stop) num_threads(newCoordinates.size())
        for (int i = 0; i < newCoordinates.size(); ++i) {
            if (!stop) {
                int childValue = 0;
                unsigned long long newBoard[TABLESIZE];

                for (int n = 0; n < TABLESIZE; ++n)
                    newBoard[n] = board[n];

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

                    if (childValue >= -5000000 && !stop) {
                        bestValue = std::max(bestValue, childValue);
                    }
                    else {
                        bestValue = childValue;
                    }
                    if (beta <= bestValue)
                        stop = true;
                } else {
                    childValue = alphaBeta(newBoard, depth - 1, true, playing, opponent, alpha, bestValue,
                                           bF);

                    if (childValue <= 5000000 && !stop) {
                        bestValue = std::min(bestValue, childValue);
                    }
                    else {
                        bestValue = childValue;
                    }
                    if (bestValue <= alpha)
                        stop = true;
                }
            }
        }
    }

    return (bestValue);
}
