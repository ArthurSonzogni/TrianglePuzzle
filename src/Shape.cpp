#include "Shape.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr float triangle_diameter = sqrt(1.0*1.0 - 0.5*0.5);
constexpr float triangle_radius   = triangle_diameter * 2.0 / 3.0;
constexpr float triangle_scale = 128;

sf::Vector2f getTriangleCenter(int x, int y)
{
  if ( (x%2)==(y%2)) // up triangle
  {
    return triangle_scale * sf::Vector2f(
        0.5+x*0.5,
        triangle_diameter*y + triangle_radius*0.5);
  }
  else // down triangle
  {
    return triangle_scale * sf::Vector2f(
        0.5+x*0.5,
        triangle_diameter*y + triangle_diameter - triangle_radius*0.5);
  }
}


Shape::Shape()
{
  dim_x = 8;
  dim_y = 8;
  static int mm = 6138;
  mm = 6138;
  static bool tt = false;
  tt = !tt;
  for(int y = 0; y<dim_y; ++y)
  for(int x = 0; x<dim_x; ++x)
  {
    mm = 97*mm + 13;
    bool ok =  (mm%3==0) == tt;
    block.push_back(ok);
  }
  color = sf::Color(255,0,0);
}

void Shape::draw(sf::RenderWindow& screen)
{
  sf::CircleShape triangle[2];
  float dim = triangle_radius * triangle_scale;
  triangle[0] = sf::CircleShape(dim,3);
  triangle[0].setOrigin(dim,dim);
  triangle[0].setFillColor(color);
  triangle[1] = triangle[0];
  triangle[1].rotate(180);

  for(int y = 0; y<dim_y; ++y)
  for(int x = 0; x<dim_x; ++x)
  if (block[x+dim_x*y])
  {
    bool side = ((x%2) == (y%2)); // up triangle
    triangle[side].setPosition(getTriangleCenter(x,y)+sf::Vector2f(pos_x,pos_y));
    screen.draw(triangle[side]);
  }
}



// indexed by
// side (down then up)
// triangle index (0,1,2)
// triangle coordinate (x,y)
constexpr float triangle_position[2][4][2] =
{
  {
    {cos(2.0*M_PI*(0.0/3.0+1.0/4.0)),-sin(2.0*M_PI*(0.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(1.0/3.0+1.0/4.0)),-sin(2.0*M_PI*(1.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(2.0/3.0+1.0/4.0)),-sin(2.0*M_PI*(2.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(0.0/3.0+1.0/4.0)),-sin(2.0*M_PI*(0.0/3.0+1.0/4.0))}
  },
  {
    {cos(2.0*M_PI*(0.0/3.0+1.0/4.0)), sin(2.0*M_PI*(0.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(2.0/3.0+1.0/4.0)), sin(2.0*M_PI*(2.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(1.0/3.0+1.0/4.0)), sin(2.0*M_PI*(1.0/3.0+1.0/4.0))},
    {cos(2.0*M_PI*(0.0/3.0+1.0/4.0)), sin(2.0*M_PI*(0.0/3.0+1.0/4.0))}
  }
};

bool Shape::is_in(float mouse_x, float mouse_y)
{
  mouse_x -= pos_x;
  mouse_y -= pos_y;
  for(int y = 0; y<dim_y; ++y)
  for(int x = 0; x<dim_x; ++x)
  if (block[x+dim_x*y])
  {
    bool side = ((x%2) == (y%2)); // up triangle
    auto position = getTriangleCenter(x,y);
    float x1 = (mouse_x - position.x) / (triangle_scale * triangle_radius);
    float y1 = (mouse_y - position.y) / (triangle_scale * triangle_radius);
    bool in = true;
    //std::cout << "side = " << side << std::endl;
    for(int i = 0; i<3; ++i)
    {
      float x2 = triangle_position[side][i  ][0];
      float y2 = triangle_position[side][i  ][1];
      float x3 = triangle_position[side][i+1][0];
      float y3 = triangle_position[side][i+1][1];
      float dx1 = x3 - x2;
      float dy1 = y3 - y2;
      float dx2 = x1 - x2;
      float dy2 = y1 - y2;
      float dist =  ( dx1*dy2 - dx2*dy1 );
      if ( dist >= 0) 
      {
        in = false;
        break;
      }
    }
    if (in)
    {
      return true;
    }
  }
  return false;
}

void Shape::align(float fraction)
{
  float Y = std::round(pos_y / ( triangle_diameter * triangle_scale) );
  float X = std::round(pos_x / triangle_scale - 0.5 * pos_y / (  triangle_diameter * triangle_scale ) );

  float y = ( Y ) * ( triangle_diameter * triangle_scale );
  float x = ( X + 0.5 * y / ( triangle_diameter * triangle_scale ) ) * ( triangle_scale );
  //float Y = std::round(pos_x / (0.5*triangle_scale) + pos_y / (triangle_diameter * triangle_scale));

  pos_x += (x - pos_x) * fraction;
  pos_y += (y - pos_y) * fraction;
  //pos_y += (goal.y - pos_y) * fraction;
}
