#pragma once


#include "point.hpp"
#include "lightsource.hpp"
#include "screen_vector/vector.hpp"
#include "screen_vector/color.hpp"

#include <vector>

class Object;
namespace rt { class image; } 
class Ray;

class Scene {
  private:
    double fov;

    double screen_width;

    std::vector<Object*> objects;

    Point camera;

    LightSource light_source;

    rt::vector view_direction;


  public:
    //Create a new Scene from the following data:
    //  * light : the light source of the scene (copied into the scene)
    //  * camera : the point of origin of the camera
    //  * screen_width : the width of the screen (NOT in pixels)
    //  * fov : The field of view. This is an angle in radians that defines the width of the view. The narrower it is, the further is the screen from the camera (and the closer to the objects displayed)
    //  * view_direction : from the camera, the direction of the upper left corner of the screen.
    Scene(const LightSource & light, const Point & camera, double screen_width, double fov, const rt::vector & view_direction);

    //Add an object to the scene.
    //
    //Note that no copy will be made of the object, the Scene will store a reference. Make sure the object lifetime is long enough!
    void add_object(Object & obj);

    //Renders the whole scene in `img`.
    virtual void render(rt::image & img);

    //Computes the color of a ray.
    //This is used for the original rays from the camera, but can also be used recursively by an object.
    virtual rt::color render_ray(const Ray & ray);

    virtual Object * get_interceptor(const Ray & ray);

    //Returns the width of the screen.
    double get_screen_width() const;

    //Returns the field of view of the scene (an angle in radians).
    double get_fov() const;

    //Returns the point where the camera stands.
    Point get_camera() const;

    //Returns the direction of the upper left corner of the screen from the PoV of the camera.
    rt::vector get_view_direction() const;

    //Sets the field of view to `angle`.
    void set_fov(double angle);

    //Moves the camera to the point `p`
    void set_camera(const Point & p);

    //Points the upper left corner of the screen towards `v` from the camera.
    void set_view_direction(const rt::vector & v);

};
