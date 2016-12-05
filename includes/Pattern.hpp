//
// Created by francois on 05/12/16.
//

#ifndef GOMOKU_PATTERN_H
#define GOMOKU_PATTERN_H

#include <string>

class Pattern {
    std::string pattern;
    int         score;
    int         direction;
    int         x;
    int         y;
public:
    bool operator==(const Pattern &rhs) const;

    bool operator!=(const Pattern &rhs) const;

public:
    int getDirection() const;

    void setDirection(int direction);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

public:
    const std::string &getPattern() const;

    void setPattern(const std::string &pattern);

    int getScore() const;

    void setScore(int score);
};


#endif //GOMOKU_PATTERN_H
