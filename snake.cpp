//
// snake.cpp for snake in /home/simomb_s/semestre4/test_maison/c++/snake
//
// Made by stephanedarcy simomba
// Login   <simomb_s@epitech.net>
//
// Started on  Fri Mar 18 07:36:45 2016 stephanedarcy simomba
// Last update Fri Apr 15 08:13:31 2016 stephanedarcy simomba
//

#include "snake.h"

Character::Character(int col, int row) {
  x = col;
  y = row;
}

Character::Character() {
  x = 0;
  y = 0;
}

GetMap::GetMap() {
  std::string	str;
  initscr();
  nodelay(stdscr, true); //the getch not wait the user press a key
  keypad(stdscr, true);
  //noecho();
  curs_set(0);
  getmaxyx(stdscr, width, height); //get the max height and width
  // Reservé pour la lib
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLUE, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_WHITE);
  //
  for (int i = 0; i < width; i++) {
    str.erase();
    for (int j = 0; j < height; j++) {
      str += ".";
    }
    this->map.push_back(str);
  }
}

snakeclass::snakeclass() {
  // init a few variables
  partchar = '*';
  oldalchar = (char)219;
  foo = '*';
  food.x = 0;
  food.y = 0;
  for (int i=0; i < 5; i++) {
    snake.push_back(Character((5 + i), 8));
    Map.map[5 + i][8] = 'X';
  }
  Map.points = 0;
  del = 110000;
  get = false;
  direction = 'l';
  srand(time(0));
  putfood();
}

snakeclass::~snakeclass() {
  printw("Destructor\n");
  endwin();
}

void	snakeclass::putfood() {
  while (1) {
    int	tmpx = rand() % Map.width+1;
    int	tmpy = rand() % Map.height+1;
    for (unsigned int i = 0; i < snake.size(); i++) {
      if (snake[i].x == tmpx && snake[i].y == tmpy)
	continue;
    }
    if (tmpx >= Map.width-2 || tmpy >= Map.height-3)
      continue;
    food.x = tmpx;
    food.y = tmpy;
    break;
  }
  Map.map[food.x][food.y] = foo;
  move(food.y, food.x);
  addch(foo);
  refresh();
}

bool	snakeclass::collision() {
  if (snake[0].x == 0 || snake[0].x == Map.width-2 || snake[0].y == 0 || snake[0].y == Map.height-1)
    return true;

  for (unsigned int i=2; i < snake.size(); i++)
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      return true;
  if (snake[0].x == food.x && snake[0].y == food.y) {
    get = true;
    putfood();
    Map.points += 10;
    if ((Map.points % 100) == 0)
      del -= 10000;
  } else
    get = false;
  return false;
}

void	snakeclass::movesnake() {
  int	tmp = getch();

  switch(tmp) {
  case KEY_LEFT:
    if (direction != 'r')
      direction = 'l';
    break ;
  case KEY_UP:
    if (direction != 'd')
      direction = 'u';
    break ;
  case KEY_DOWN:
    if (direction != 'u')
      direction = 'd';
    break ;
  case KEY_RIGHT:
    if (direction != 'l')
      direction = 'r';
    break ;
  case KEY_BACKSPACE:
    direction = 'q';
    break ;
  }
  if (!get) {
    Map.map[snake[snake.size() - 1].x][snake[snake.size() - 1].y] = '.'; //attention
    snake.pop_back();
  }
  if (direction == 'l')
    snake.insert(snake.begin(), Character(snake[0].x, snake[0].y - 1));
  else if (direction == 'r')
    snake.insert(snake.begin(), Character(snake[0].x, snake[0].y + 1));
  else if (direction == 'u')
    snake.insert(snake.begin(), Character(snake[0].x - 1, snake[0].y));
  else if (direction == 'd')
    snake.insert(snake.begin(), Character(snake[0].x + 1, snake[0].y));
  Map.map[snake[0].x][snake[0].y] = 'X'; //attention
}

GetMap	snakeclass::getMap() const {
  return this->Map;
}

void	snakeclass::aff_map() {
  move(0, 0);
  for (int i = 0; i < Map.width; i++) {
    for (int j = 0; j < Map.height; j++) {
      if (i == 0 || j == 0 || j == (Map.height - 1) || i == (Map.width - 2)) {
	attron(A_REVERSE | A_INVIS | COLOR_PAIR(2));
	addch(Map.map[i][j]);
	attroff(A_REVERSE | A_INVIS | COLOR_PAIR(2));
      }
      else if (Map.map[i][j] == '.') {
	attron(A_REVERSE | COLOR_PAIR(1));
	addch(Map.map[i][j]);
	attroff(A_REVERSE | COLOR_PAIR(1));
      }
      else if (Map.map[i][j] == 'X') {
	attron(A_REVERSE | A_INVIS | COLOR_PAIR(2));
	addch(Map.map[i][j]);
	attroff(A_REVERSE | A_INVIS | COLOR_PAIR(2));
      }
      else if (Map.map[i][j] == '*') {
	attron(A_REVERSE | A_INVIS | COLOR_PAIR(3));
	addch(Map.map[i][j]);
	attroff(A_REVERSE | A_INVIS | COLOR_PAIR(3));
      } else
	addch(Map.map[i][j]);
    }
  }
  move(Map.width-1, 0);
  printw("%d", Map.points);
}

void	snakeclass::Play() {
  while (1)
    {
      if (collision()) {
	printw("Game over");
	break ;
      }
      movesnake();
      aff_map();
      if (direction == 'q')
	break ;
      usleep(del);
    }
}
