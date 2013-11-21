
#include "scene.hpp"
#include "object.hpp"
#include "screen_vector/image.hpp"
#include "ray.hpp"

#include <cmath>

//Create a new Scene from the following data:
//  * light : the light source of the scene (copied into the scene)
//  * camera : the point of origin of the camera
//  * screen_width : the width of the screen (NOT in pixels)
//  * fov : The field of view. This is an angle in radians that defines the width of the view. The narrower it is, the further is the screen from the camera (and the closer to the objects displayed)
//  * view_direction : from the camera, the direction of the upper left corner of the screen.
Scene::Scene(const LightSource & light, const Point & camera, double screen_width, double fov, const rt::vector & view_direction):
    fov(fov), screen_width(screen_width), objects(0), camera(camera), light_source(light), view_direction(view_direction)
{
}

//Add an object to the scene.
//
//Note that no copy will be made of the object, the Scene will store a reference. Make sure the object lifetime is long enough!
void Scene::add_object(Object & obj) {
    this->objects.push_back(&obj);
}

//Renders the whole scene in `img`.
void Scene::render(rt::image & img) {
    double pixel_size = img.width()/this->screen_width;
    double teta = fov/(2.0*img.width());
    rt::vector lateral_delta(pixel_size*(view_direction.x*sin(teta) + view_direction.z*cos(teta)), pixel_size*view_direction.y, pixel_size*(view_direction.z*sin(teta)-view_direction.x*cos(teta)));
    rt::vector vertical_delta = view_direction ^ lateral_delta;

    double sin_half_fov = sin(fov/2.);
    double corner_distance = screen_width*screen_width/(4.*sin_half_fov*sin_half_fov);

    Point p(camera);
    p += (corner_distance * view_direction);
    for(int i = 0 ; i < img.height() ; ++i) {
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
    if (interceptor) {
        return rt::color::BLACK;
    }
    rt::color indirect = interceptor->render_indirect(ray, *this);
    rt::color direct = interceptor->render_direct(ray, *this, light_source);
    // Pardon the C-like casts, but reinterpret_cast
    double red = static_cast<double>(indirect.get_red())+direct.get_red();
    red /= red+1.;
    double green = static_cast<double>(indirect.get_green())+direct.get_green();
    green /= green+1.;
    double blue = static_cast<double>(indirect.get_blue())+direct.get_blue();
    blue /= blue+1.;
    return rt::color(static_cast<unsigned char>(ceil(red*256.0)), static_cast<unsigned char>(ceil(green*256.0)), static_cast<unsigned char>(ceil(green*256.0)));
}

Object * Scene::get_interceptor(const Ray & ray) {
    Object * interceptor = 0;
    double minimum = 0;
    double current = 0;
    for (std::vector<Object *>::const_iterator it = objects.begin() ; it != objects.end() ; ++it) {
        current = (*it)->intersects(ray);
        if (current > 0 && current < minimum) {
            interceptor = *it;
            minimum = current;
        }
    }
    return interceptor;
}

//Returns the width of the screen.
double Scene::get_screen_width() const {
    return screen_width;
}

//Returns the field of view of the scene (an angle in radians).
double Scene::get_fov() const {
    return fov;
}

//Returns the point where the camera stands.
Point Scene::get_camera() const {
    return camera;
}

//Returns the direction of the upper left corner of the screen from the PoV of the camera.
rt::vector Scene::get_view_direction() const {
    return view_direction;
}

//Sets the field of view to `angle`.
void Scene::set_fov(double angle) {
    fov = angle;
}

//Moves the camera to the point `p`
void Scene::set_camera(const Point & p) {
    camera = p;
}

//Points the upper left corner of the screen towards `v` from the camera.
void Scene::set_view_direction(const rt::vector & v) {
    view_direction = v;
}

