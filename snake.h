/*
** snake.h for snake in /home/simomb_s/semestre4/test_maison/c++/snake
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri Mar 18 07:43:41 2016 stephanedarcy simomba
** Last update Sat Apr  2 05:08:35 2016 stephanedarcy simomba
*/

#ifndef SNAKE_H_
# define SNAKE_H_

#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

struct Character {
  int	x, y;
  Character(int col, int row);
  Character();
};

struct GetMap {
  int	width;
  int	height;
  int	points;
  std::vector<std::string> map;
  GetMap();
};

class snakeclass {

  GetMap	Map;
  int		points;
  int		del;
  char		direction, partchar, oldalchar, foo;
  bool		get;
  Character	food;
  std::vector<Character> snake;

  void		putfood();
  bool		collision();
  void		movesnake();
  void		aff_map();
 public:
  snakeclass();
  ~snakeclass();
  GetMap	getMap() const;
  void		Play();
};

#endif /* !SNAKE_H_ */
