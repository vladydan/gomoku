#include <algorithm>
#include "Player.hpp"

Player::Player(int color, std::string name, Player::PlayerType type) : _color(color), _name(name), _type(type), _broke(0)
{
}

std::string	Player::getName() const
{
  return (_name);
}

Player::PlayerType	Player::getType() const
{
  return (_type);
}

int		Player::getBroke() const
{
  return (_broke);
}

int		Player::getColor() const
{
  return (_color);
}

void		Player::setBroke(int const& value)
{
  _broke = value;
}

const std::list<Pattern> &Player::getPatterns() const {
  return patterns;
}

void Player::addPattern(Pattern const &pat) {
  if (std::find_if(patterns.begin(), patterns.end(), [&] (Pattern const &p) {return p.getPattern() == pat.getPattern();}) == patterns.end())
    patterns.push_back(pat);
}
