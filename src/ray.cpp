
#include "ray.hpp"

//Construct a ray from a point of origin and a direction vector. The latter doesn't have to be normalized.
Ray::Ray(const Point & origin, const rt::vector & direction): origin(origin), direction(direction) {
}

//Construct a ray originating from `origin` and passing through the point `through`.
Ray::Ray(const Point & origin, const Point & through): origin(origin), direction(through-origin) {
}

// Returns the point of origin of the ray
Point Ray::get_origin() const {
    return origin;
}

// Returns the normalized vector representing the direction of the ray
rt::vector Ray::get_direction() const {
    return direction;
}

