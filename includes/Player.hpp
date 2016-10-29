#pragma once

#include <string>

#define BLACK 0
#define WHITE 1

class Player
{
public:
  enum PlayerType
    {
      PLAYER = 0,
      IA
    };
private:
  int		_color;
  std::string	_name;
  PlayerType	_type;
  int		_broke;

public:
  explicit Player(int, std::string = "Player", PlayerType = IA);
  virtual ~Player() {}

  std::string	getName() const;
  PlayerType	getType() const;
  int		getBroke() const;
  int		getColor() const;
  void		setBroke(int const&);
};
