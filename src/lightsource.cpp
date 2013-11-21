
#include "lightsource.hpp"

Point LightSource::get_origin() const {
    return origin;
}


//The color of the light source.
rt::color LightSource::get_color() const {
    return color;
}

LightSource::LightSource(const Point & point, const rt::color & color): origin(point), color(color) {
}

