#pragma once


#include "point.hpp"
#include "screen_vector/color.hpp"

//A source of white light.
class LightSource {
  private:
    rt::color color;

  protected:
    Point origin;


  public:
    Point get_origin() const;


  public:
    //The color of the light source.
    rt::color get_color() const;

    LightSource(const Point & point, const rt::color & color);
    LightSource();

};
