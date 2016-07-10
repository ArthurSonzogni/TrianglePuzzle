#include "Game.hpp"

Game::Game():
  window(sf::VideoMode(640, 480), "The Game"),
  state("running")
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  window.create(sf::VideoMode(800,600),"The Game",sf::Style::Default,settings);

  shapes.emplace_back();
  shapes.back().color = sf::Color(200,0,0,200);
  shapes.emplace_back();
  shapes.back().color = sf::Color(0,200,0,200);
}

void Game::poolEvent()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    // fermeture de la fenêtre lorsque l'utilisateur le souhaite
    if (event.type == sf::Event::Closed)
      window.close();
  }
}

void Game::play()
{
  Shape* shape_held = nullptr;
  float  shape_held_start_x = 0.0;
  float  shape_held_start_y = 0.0;
  float  shape_held_start_mouse_x = 0.0;
  float  shape_held_start_mouse_y = 0.0;
  while(state == "running")
  {
    poolEvent();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      auto mouse = sf::Mouse::getPosition(window);
      if (shape_held)
      {
        shape_held->pos_x = shape_held_start_x + mouse.x - shape_held_start_mouse_x;
        shape_held->pos_y = shape_held_start_y + mouse.y - shape_held_start_mouse_y;
      }
      else
      {
        for(auto& s : shapes)
        {
          if (s.is_in(mouse.x,mouse.y))
          {
            std::swap(s,shapes.back());
            shape_held = &shapes.back();
            shape_held_start_x = shape_held->pos_x; 
            shape_held_start_y = shape_held->pos_y; 
            shape_held_start_mouse_x = mouse.x;
            shape_held_start_mouse_y = mouse.y;
            break;
          }
        }
      }
    }
    else
    {
      shape_held = nullptr;
    }

    for(auto& s : shapes)
      s.align(0.1);


    window.clear(sf::Color(255,255,255));

    for(auto& s : shapes)
      s.draw(window);

    window.display();
  }
}
