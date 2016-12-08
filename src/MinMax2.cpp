#include <omp.h>
#include "MinMax.hh"

std::vector<coords>		MinMax::getNextMove(unsigned long long *board, Player playing, Player opponent) {
    std::vector<coords*> coord;

    for (int y = 0; y < Y_SIZE; y++) {
        for (int x = 0; x < X_SIZE; x++) {
            if (Game::getValue(board, x, y, EMPTYMASK, 0) == 0 &&
                Game::getValue(board, x, y, ZONE, ZONEDEC) == 1) {
                coords *c = new coords;
                c->y = y;
                c->x = x;
                coord.push_back(c);
            }
        }
    }

    if (coord.size() == 0) {
        coords c = new coords;
        c->x = 10;
        c->y = 10;
        coord.push_back(c);
        return (coord);
    }

    #pragma omp parallel for
    for (auto it = coord.begin() ; it != coord.end() ; ++it) {
        coords *c = (*it);
        int x = c->x;
        int y = c->y;
        coordinates.erase(it);

        Game::changeValue(board, x, y, EMPTYMASK, 0, 1);
        Game::changeValue(board, x, y, COLORMASK, 1, playing.getColor());
        Game::changeAround(board, x, y);
        Game::changeAligns(board, x, y);
        Game::affectBreakable(board, x, y, &playing, 0, NULL);
        Game::changeBreakable(board, x, y);

        c.at(i)->value = MinMax::alphaBeta(board, coord, 3, false, playing, opponent, -2147483648, 2147483647);

        Game::changeValue(board, x, y, EMPTYMASK, 0, 0); /* /!\ A verifier /!\ */
        Game::changeValue(board, x, y, COLORMASK, 1, 0); /* /!\ A verifier /!\ */
        Game::changeAround(board, x, y);
        Game::changeAligns(board, x, y);
        Game::affectBreakable(board, x, y, &playing, 0, NULL);
        Game::changeBreakable(board, x, y);

        coordinates.insert(it, c);
    }

    std::sort(coord.begin(), coord.end(),
              [](const coords *first, const coords *second) -> bool {
                  if (first->value == second->value) {
                      return ((std::rand()%2) == 0);
                  }
                  return first->value > second->value;
              });

    for (int i = 0, length = coord.size(); i < length; ++i)
        std::cout << coord.at(i)->x << " " << coord.at(i)->y << " " << coord.at(i)->value << std::endl;
    return (coord);
}

int		MinMax::alphaBeta(unsigned long long* board, std::vector<coords> const &coordinates,
				  short depth, bool maximisingPlayer, Player playing, Player opponent,
				  int alpha, int beta) {
    int bestValue = 0;

    if (!Game::checkEnd(board, false) || playing.getBroke() >= 10 || opponent.getBroke() >= 10) {
        if (playing.getBroke() >= 10) {
            return (10000000);
        } else if (opponent.getBroke() >= 10) {
            return (-10000000);
        }
        if (maximisingPlayer) {
            return (10000000);
        } else {
            return (-10000000);
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

    for (auto it = coord.begin() ; it != coord.end() ; ++it)
      {
	coords *c = (*it);
	int	x = c->x;
	int	y = c->y;
	coordinates.erase(it);

        if (maximisingPlayer)
	  {
            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
            Game::changeValue(newBoard, x, y, COLORMASK, 1, opponent.getColor());
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &opponent, 0, NULL);
            Game::changeBreakable(newBoard, x, y);

            childValue = alphaBeta(board, coordinates, depth - 1, false, playing, opponent, bestValue, beta);

            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 0); /* /!\ A verifier /!\ */
            Game::changeValue(newBoard, x, y, COLORMASK, 1, 0); /* /!\ A verifier /!\ */
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &opponent, 0, NULL);
            Game::changeBreakable(newBoard, x, y);

	    coordinates.insert(it);
	    if (childValue < -5000000)
                return (10000000);
            bestValue = std::max(bestValue, childValue);
            if (beta <= bestValue)
                return (bestValue);
        }
	else
	  {
            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
            Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
            Game::changeBreakable(newBoard, x, y);

            childValue = alphaBeta(newBoard, newCoords, depth - 1, true, playing, opponent, alpha, bestValue);
            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 0); /* /!\ A verifier /!\ */
            Game::changeValue(newBoard, x, y, COLORMASK, 1, 0); /* /!\ A verifier /!\ */
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &opponent, 0, NULL);
            Game::changeBreakable(newBoard, x, y);

	    coordinates.insert(it);
            if (childValue > 5000000)
                return (-10000000);
            bestValue = std::min(bestValue, childValue);
            if (bestValue <= alpha)
                return (bestValue);
        }
    }
    return (bestValue);
}
