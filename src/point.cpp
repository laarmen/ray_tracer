
#include "point.hpp"

//Returns the abscissa of the point.
double Point::x() const {
    return abs;
}

//Returns the ordinate of the point.
double Point::y() const {
    return ord;
}

//Returns the applicate of the point.
double Point::z() const {
    return this->app;
}

//Returns the vector from `p` to `this`
rt::vector Point::operator -(const Point & p) const {
    return rt::vector(abs-p.abs, ord-p.ord, app-p.app);
}

void  Point::operator +=(const rt::vector & v) {
    abs += v.x;
    ord += v.y;
    app += v.z;
}


