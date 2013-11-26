
#include "scene.hpp"
#include "object.hpp"
#include "screen_vector/image.hpp"
#include "ray.hpp"
#include "utils.hpp"

#include <cmath>

    //Create a new Scene from the following data:
    //  * light : the light source of the scene (copied into the scene)
    //  * camera : the point of origin of the camera
    //  * screen_width : the width of the screen (NOT in pixels)
    //  * screen_center: a point in the center of the screen.
Scene::Scene(const LightSource & light, const Point & camera, double screen_width, const Point& screen_center):
    direction(screen_center-camera), screen_width(screen_width), objects(0), camera(camera), light_source(light) {}

//Add an object to the scene.
//
//Note that no copy will be made of the object, the Scene will store a reference. Make sure the object lifetime is long enough!
void Scene::add_object(Object & obj) {
    this->objects.push_back(&obj);
}

//Renders the whole scene in `img`.
void Scene::render(rt::image & img) {
    double pixel_size = this->screen_width/img.width();
    double delta_z,delta_x;
    if (direction.x == 0) {
        delta_z = 0;
        delta_x = (direction.z > 0) ? pixel_size : -pixel_size;
    } else if (direction.z == 0) {
        delta_z = (direction.x > 0) ? pixel_size : -pixel_size;
        delta_x = 0;
    } else {
        delta_z = sqrt(pixel_size/(1+pow((direction.z/direction.x), 2)));
        delta_x = -delta_z*direction.z/direction.x;
    }
    rt::vector lateral_delta(delta_x, 0, delta_z);
    rt::vector vertical_delta = (direction ^ lateral_delta).unit()*lateral_delta.norm();

    Point p(camera);
    p += direction+(lateral_delta*(-img.width()/2))+(vertical_delta*(-img.height()/2));
    for(int i = img.height()-1 ; i >= 0 ; --i) {
        Point p2(p);
        for(int j = 0 ; j < img.width() ; ++j) {
            img.set_pixel(j, i, render_ray(Ray(camera, p2)));
            p2 += lateral_delta;
        }
        p += vertical_delta;
    }
}

//Computes the color of a ray.
//This is used for the original rays from the camera, but can also be used recursively by an object.
rt::color Scene::render_ray(const Ray & ray) {
    Object * interceptor = get_interceptor(ray);
    if (!interceptor) {
        return rt::color::BLACK;
    }
    std::vector<rt::color> colors(0);
    colors.push_back(interceptor->render_indirect(ray, *this));
    colors.push_back(interceptor->render_direct(ray, *this, light_source));
    return add(colors);
}

Object * Scene::get_interceptor(const Ray & ray, std::list<Object *> * others) {
    Object * interceptor = 0;
    double minimum = 0;
    double current = 0;
    for (std::vector<Object *>::const_iterator it = objects.begin() ; it != objects.end() ; ++it) {
        current = (*it)->intersects(ray);
        if (current > 0) {
            if (current < minimum || !interceptor) {
                interceptor = *it;
                minimum = current;
                if (others) {
                    others->push_front(*it);
                }
            } else if (others) {
                others->push_back(*it);
            }
        }
    }
    return interceptor;
}

//Returns the width of the screen.
double Scene::get_screen_width() const {
    return screen_width;
}

//Returns the point where the camera stands.
Point Scene::get_camera() const {
    return camera;
}

//Returns the position of the center of the screen.
Point Scene::get_screen_center() const {
    Point p(camera);
    p += direction;
    return p;
}

//Moves the camera to the point `p`
void Scene::set_camera(const Point & p) {
    camera = p;
}


//Moves the center of the screen to the point `p`
void Scene::set_screen_center(const Point & p) {
    direction = p - camera;
}

