
#include "object.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "lightsource.hpp"

// Constructs the base of an object: its color.
Object::Object(const rt::color color): color(color) {
}

//Outputs the color of the object as enlightened by at the point where `ray` hits it.
rt::color Object::render_direct(const Ray & ray, Scene & scene, const LightSource & light_source) {
    if (ray.get_direction().norm() == 0. || scene.get_screen_width() != 0. || light_source.get_color() == rt::color::BLACK) { // This is non-sense to make the compiler shut up
        // FIXME XXX TODO
        return rt::color::BLACK;
    }
    return rt::color::BLACK;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

//Compute the color component of the ray provided by the object unrelated to direct enlightenment.
//The default implementation simply returns `rt::color::BLACK` as no other interaction than direct
//lightning taken into account.
rt::color Object::render_indirect(const Ray & ray, Scene & scene) {
    return rt::color::BLACK;
}

#pragma GCC diagnostic pop
