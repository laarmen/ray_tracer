#pragma once


#include "point.hpp"
#include "screen_vector/vector.hpp"

class Ray {
  private:
    Point origin;

    rt::vector direction;


  public:
    //Construct a ray from a point of origin and a direction vector. The latter doesn't have to be normalized.
    Ray(const Point & origin, const rt::vector & direction);

    //Construct a ray originating from `origin` and passing through the point `through`.
    Ray(const Point & origin, const Point & through);

    // Returns the point of origin of the ray
    Point get_origin() const;

    // Returns the normalized vector representing the direction of the ray
    rt::vector get_direction() const;
};
