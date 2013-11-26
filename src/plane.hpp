#pragma once


#include "object.hpp"
#include "point.hpp"
#include "screen_vector/vector.hpp"

class Plane: public Object {
  private:
    Point p;
    rt::vector normale;

  public:
    //If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
    //Otherwise, returns a negative number.
    virtual double intersects(const Ray & ray) const;

    //Computes the impact of a ray onto the object.
    //Returns an impact with a null normal vector if the ray doesn't hit the object at all.
    virtual Impact get_impact(const Ray & ray) const;

    Plane(const Point & p, const rt::vector & normale, const rt::color & color);
};



