#include "config.h"
#include <iostream>
#include "Game.hpp"

int main(int argc, const char *argv[])
{
  std::cout << "VERSION = " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;  
  Game game;
  game.play();

  return 0;
}
