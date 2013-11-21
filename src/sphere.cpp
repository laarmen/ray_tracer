
#include "sphere.hpp"
#include "ray.hpp"

//If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
//Otherwise, returns a negative number.
double Sphere::intersects(const Ray & ray) const {
    //XXX TODO!!!
    return ray.get_direction().norm();
}

Sphere::Sphere(const Point & center, double radius, const rt::color & color): Object(color), center(center), radius(radius) {
}

//Computes the impact of a ray onto the object.
//Returns an impact with a null normal vector if the ray doesn't hit the object at all.
Impact Sphere::get_impact(const Ray & ray) const {
    //XXX TODO!!
    if (ray.get_direction().norm() == 0.) {
        return Impact();
    }
    return Impact();
}

