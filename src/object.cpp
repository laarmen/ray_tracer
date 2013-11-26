
#include "object.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "utils.hpp"
#include "lightsource.hpp"
#include "material.hpp"
#include <algorithm>

// Useful if one catches one's own rays because of floating error.
#define OWNRAY_EPSILON 0.00000000000000075

// Constructs the base of an object: its color.
Object::Object(const rt::color color, Material * material): color(color), material(material) {
}

//Outputs the color of the object as enlightened by at the point where `ray` hits it.
rt::color Object::render_direct(const Ray & ray, Scene & scene, const LightSource & light_source) {
    rt::color basic = compose(light_source.get_color(), color);
    Impact imp = get_impact(ray);
    Ray to_light(imp.point, light_source.get_origin());
    double scalar = -(ray.get_direction() | imp.normale);
    if (((light_source.get_origin()-imp.point) | imp.normale) <= 0) {
        return rt::color::BLACK;
    }
    std::list<Object *> others;
    Object* interceptor = scene.get_interceptor(to_light, &others);
    // In case there has been mixups due to rounding errors and the object catches
    // its own ray back to the light when it shouldn't (which is NOT always the case)
    // detect it
    if (interceptor && (interceptor != this || intersects(to_light) >= OWNRAY_EPSILON || others.size() > 1)) {
        return rt::color::BLACK;
    }
    return rt::color(
            static_cast<unsigned char>(scalar*basic.get_red()),
            static_cast<unsigned char>(scalar*basic.get_green()),
            static_cast<unsigned char>(scalar*basic.get_blue())
        );
}


// Make GCC shut up about that, it is meant to be overloaded and only provides a backup.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

//Compute the color component of the ray provided by the object unrelated to direct enlightenment.
//The default implementation simply returns `rt::color::BLACK` as no other interaction than direct
//lightning taken into account.
rt::color Object::render_indirect(const Ray & ray, Scene & scene) {
    Impact imp = get_impact(ray);
    if (material) {
        return material->indirect_rendering(ray, scene, imp, *this);
    }
    return rt::color::BLACK;
}

#pragma GCC diagnostic pop
