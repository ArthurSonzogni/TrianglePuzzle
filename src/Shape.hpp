#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Shape
{
  public:
    Shape();
    bool is_in(float mouse_x, float mouse_y);
    void draw(sf::RenderWindow& screen);
    void align(float fraction);

    float pos_x = 0.0;
    float pos_y = 0.0;
    sf::Color color;
  private:
    int dim_x = 0;
    int dim_y = 0;
    std::vector<bool> block;
};

#endif /* end of include guard: SHAPE_H */
