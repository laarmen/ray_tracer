#pragma once


#include "screen_vector/color.hpp"
#include "impact.hpp"

class Ray;
class Scene;
class LightSource;

//The mathematical representation of an object. This class is abstract.
class Object {
  private:
    rt::color color;

  public:
    // Constructs the base of an object: its color.
    Object(const rt::color color);

    //If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
    //Otherwise, returns a negative number.
    virtual double intersects(const Ray & r) const = 0;

    //Outputs the color of the object as enlightened by at the point where `ray` hits it.
    virtual rt::color render_direct(const Ray & ray, Scene & scene, const LightSource & light_source);

    //Compute the color component of the ray provided by the object unrelated to direct enlightenment.
    //The default implementation simply returns `rt::color::BLACK` as no other interaction than direct
    //lightning taken into account.
    virtual rt::color render_indirect(const Ray & ray, Scene & scene);

    //Computes the impact of a ray onto the object.
    //Returns an impact with a null normal vector if the ray doesn't hit the object at all.
    virtual Impact get_impact(const Ray & ray) const = 0;

};
