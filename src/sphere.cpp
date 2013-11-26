
#include "sphere.hpp"
#include "ray.hpp"
#include <algorithm>
#include <cmath>

//If the object intersects the ray, returns the distance between the origin of the ray and the intersection point.
//Otherwise, returns a negative number.
double Sphere::intersects(const Ray & ray) const {
    CoeffPoly cp = compute_coeffs(ray);
    double delta = cp.discriminant();
    if (delta <= 0) {
        return 0;
    }
    double delta_sqrt = sqrt(delta);
    double t1 = ((- cp.b + delta_sqrt)) / (2 * cp.a);
    double t2 = ((- cp.b - delta_sqrt)) / (2 * cp.a);
    if (t1 <= 0 && t2 <= 0) {
        return -42;
    }
    return std::min(std::max(t1, 0.), std::max(t2, 0.));
}

Sphere::Sphere(const Point & center, double radius, const rt::color & color): Object(color), center(center), radius(radius) {
}

//Computes the impact of a ray onto the object.
//Returns an impact with a null normal vector if the ray doesn't hit the object at all.
Impact Sphere::get_impact(const Ray & ray) const {
    Impact imp; 
    double distance = intersects(ray);
    if (distance <= 0) {
        imp.normale = rt::vector(0,0,0);
    } else {
        imp.point = Point (
            ray.get_origin().x() + distance * ray.get_direction().x,
            ray.get_origin().y() + distance * ray.get_direction().y,
            ray.get_origin().z() + distance * ray.get_direction().z
            );
        imp.normale = (imp.point-center).unit();
    }
    return imp;
}


Sphere::CoeffPoly Sphere::compute_coeffs(const Ray & r) const {
    CoeffPoly cp;
    rt::vector ac = center-r.get_origin();
    rt::vector u = r.get_direction();
    cp.a = u.x*u.x + u.y*u.y + u.z*u.z;
    cp.b = -2*(u.x * ac.x + u.y * ac.y + u.z * ac.z);
    cp.c = - radius * radius + ac.x * ac.x + ac.y * ac.y + ac.z * ac.z;
    return cp;
}
