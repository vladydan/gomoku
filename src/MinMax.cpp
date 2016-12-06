#include "MinMax.hh"

std::vector<coords>		MinMax::getNextMove(unsigned long long *board, Player playing, Player opponent) {
    std::vector<coords> coord;
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

    for (int i = 0, length = coord.size(); i < length; ++i) {
        std::vector<coords> newCoords;
        unsigned long long newBoard[Y_SIZE * X_SIZE];

        for (int n = 0, boardLength = Y_SIZE * X_SIZE; n < boardLength; ++n)
            newBoard[n] = board[n];

        int y = coord[i].y;
        int x = coord[i].x;
        for (int n = 0; n < length; ++n) {
            if (n != i)
                newCoords.push_back(coord.at(n));
        }
        Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
        Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
        Game::changeAround(newBoard, x, y);
        Game::changeAligns(newBoard, x, y);
        Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
        Game::changeBreakable(newBoard, x, y);//ajouter une pierre noire a ces coordonnees
        coord.at(i).value = MinMax::alphaBeta(newBoard, newCoords, 3, true, playing, opponent);
    }

    std::sort(coord.begin(), coord.end(),
              [](const coords &first, const coords &second) -> bool {
                  return first.value > second.value;
              });

    for (int i = 0, length = coord.size(); i < length; ++i)
        std::cout << coord.at(i).x << " " << coord.at(i).y << " " << coord.at(i).value << std::endl;
    return (coord);
}

int		MinMax::alphaBeta(unsigned long long* board, std::vector<coords> const &coordinates,
				  short depth, bool maximisingPlayer, Player playing, Player opponent) {
    int bestValue = 0;

    if (!Game::checkEnd(board, false) || playing.getBroke() >= 10 || opponent.getBroke() >= 10) {
        if (playing.getBroke() >= 10) {
            return (1000000);
        } else if (opponent.getBroke() >= 10) {
            return (-1000000);
        }
        if (maximisingPlayer) {
            return (1000000);
        } else {
            return (-1000000);
        }
    }
    if (depth == 0) {
        bestValue = Game::getTotalScore(board, playing.getColor(), opponent.getBroke(), playing.getBroke());
        return (bestValue);
    }

    for (int i = 0, length = coordinates.size(); i < length; ++i) {
        int childValue = 0;
        std::vector<coords> newCoords;
        unsigned long long newBoard[Y_SIZE * X_SIZE];

        for (int n = 0, boardLength = Y_SIZE * X_SIZE; n < boardLength; ++n)
            newBoard[n] = board[n];

        int y = coordinates[i].y;
        int x = coordinates[i].x;
        for (int n = 0; n < length; ++n) {
            if (n != i)
                newCoords.push_back(coordinates.at(n));
        }
        if (maximisingPlayer) {
            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
            Game::changeValue(newBoard, x, y, COLORMASK, 1, opponent.getColor());
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &opponent, 0, NULL);
            Game::changeBreakable(newBoard, x, y);//ajouter une pierre noire a ces coordonnees
        }//ajouter une pierre blanche a ces coordonnees
        else {
            Game::changeValue(newBoard, x, y, EMPTYMASK, 0, 1);
            Game::changeValue(newBoard, x, y, COLORMASK, 1, playing.getColor());
            Game::changeAround(newBoard, x, y);
            Game::changeAligns(newBoard, x, y);
            Game::affectBreakable(newBoard, x, y, &playing, 0, NULL);
            Game::changeBreakable(newBoard, x, y);//ajouter une pierre noire a ces coordonnees
        }

        if (maximisingPlayer) {
            childValue = alphaBeta(newBoard, newCoords, depth - 1, false, playing, opponent);
            if (i == 0)
                bestValue = childValue;
            else
                bestValue = std::max(bestValue, childValue);
        } else {
            childValue = alphaBeta(newBoard, newCoords, depth - 1, true, playing, opponent);
            if (i == 0)
                bestValue = childValue;
            else
                bestValue = std::min(bestValue, childValue);
        }
    }
    return (bestValue);
}
