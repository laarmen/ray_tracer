#pragma once


#include "object.hpp"
#include "point.hpp"
#include "screen_vector/color.hpp"
#include "impact.hpp"

class Ray;

class Sphere : public Object {
  public:
    //If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
    //Otherwise, returns a negative number.
    virtual double intersects(const Ray & ray) const;

    Sphere(const Point & center, double radius, const rt::color & color);


  private:
    Point center;

    rt::color color;


  public:
    //Computes the impact of a ray onto the object.
    //Returns an impact with a null normal vector if the ray doesn't hit the object at all.
    virtual Impact get_impact(const Ray & ray) const;


  private:
    double radius;

};
