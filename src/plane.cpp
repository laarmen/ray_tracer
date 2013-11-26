#include "plane.hpp"
#include "ray.hpp"
#include "impact.hpp"


Plane::Plane(const Point & p, const rt::vector & normale, const rt::color & color): Object(color), p(p), normale(normale.unit()) {}


//If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
//Otherwise, returns a negative number.
double Plane::intersects(const Ray & ray) const {
    double s1 = ray.get_direction() | normale;
    double s2 = normale | (p - ray.get_origin());
    if (s1 == 0. || s2 == 0.) {
        return -42.;
    }
    return s2/s1;
}

//Computes the impact of a ray onto the object.
//Returns an impact with a null normal vector if the ray doesn't hit the object at all.
Impact Plane::get_impact(const Ray & ray) const {
    double distance = intersects(ray);
    Impact imp;
    if (distance <= 0.) {
        imp.normale = rt::vector(0,0,0);
    } else {
        imp.point = ray.get_origin();
        imp.point += ray.get_direction() * distance;
        if ((ray.get_direction() | normale) < 0.) {
            imp.normale = normale;
        } else {
            imp.normale = normale * -1.;
        }
    }
    return imp;
}
