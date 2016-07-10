#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Shape.hpp"

class Game
{
  public:
    Game();
    void play();
  private:
    sf::RenderWindow window;
    std::string state;
    void poolEvent();
    std::vector<Shape> shapes;
};

#endif /* end of include guard: GAME_H */
