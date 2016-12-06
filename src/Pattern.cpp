//
// Created by francois on 05/12/16.
//

#include "Pattern.hpp"

const std::string &Pattern::getPattern() const {
    return pattern;
}

void Pattern::setPattern(const std::string &pattern) {
    Pattern::pattern = pattern;
}

int Pattern::getScore() const {
    return score;
}

void Pattern::setScore(int score) {
    Pattern::score = score;
}

int Pattern::getDirection() const {
    return direction;
}

void Pattern::setDirection(int direction) {
    Pattern::direction = direction;
}

int Pattern::getX() const {
    return x;
}

void Pattern::setX(int x) {
    Pattern::x = x;
}

int Pattern::getY() const {
    return y;
}

void Pattern::setY(int y) {
    Pattern::y = y;
}

bool Pattern::operator==(const Pattern &rhs) const {
    return pattern == rhs.pattern &&
           score == rhs.score &&
           direction == rhs.direction &&
           x == rhs.x &&
           y == rhs.y;
}

bool Pattern::operator!=(const Pattern &rhs) const {
    return !(rhs == *this);
}

int Pattern::getAverageScore() const {
    return averageScore;
}

void Pattern::setAverageScore(int averageScore) {
    Pattern::averageScore = averageScore;
}
