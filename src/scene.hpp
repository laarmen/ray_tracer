#pragma once


#include "point.hpp"
#include "lightsource.hpp"
#include "screen_vector/vector.hpp"
#include "screen_vector/color.hpp"

#include <vector>
#include <list>

class Object;
namespace rt { class image; } 
class Ray;

class Scene {
  private:
    rt::vector direction;

    double screen_width;

    std::vector<Object*> objects;

    Point camera;

    LightSource light_source;

  public:
    //Create a new Scene from the following data:
    //  * light : the light source of the scene (copied into the scene)
    //  * camera : the point of origin of the camera
    //  * screen_width : the width of the screen (NOT in pixels)
    //  * screen_center: a point in the center of the screen.
    Scene(const LightSource & light, const Point & camera, double screen_width, const Point& screen_center);

    //Add an object to the scene.
    //
    //Note that no copy will be made of the object, the Scene will store a reference. Make sure the object lifetime is long enough!
    void add_object(Object & obj);

    //Renders the whole scene in `img`.
    virtual void render(rt::image & img);

    //Computes the color of a ray.
    //This is used for the original rays from the camera, but can also be used recursively by an object.
    virtual rt::color render_ray(const Ray & ray);

    // Given a ray, gives out the first object of the scene to intercept it,
    // or the null pointer if there aren't any.
    // If you wish, you can also get all the interceptors (even the farther ones)
    // stored in the `others` list.
    virtual Object * get_interceptor(const Ray & ray, std::list<Object *> * others = 0);

    //Returns the width of the screen.
    double get_screen_width() const;

    //Returns the point where the camera stands.
    Point get_camera() const;

    //Returns the position of the center of the screen.
    Point get_screen_center() const;

    //Moves the camera to the point `p`
    void set_camera(const Point & p);

    //Moves the center of the screen to the point `p`
    void set_screen_center(const Point & p);
};
