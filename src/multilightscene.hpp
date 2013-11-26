#pragma once

#include "lightsource.hpp"
#include "scene.hpp"

#include <vector>

class MultiLightScene: public Scene {
  private:
    std::vector<LightSource> sources;
  public:
    //Computes the color of a ray.
    //This is used for the original rays from the camera, but can also be used recursively by an object.
    virtual rt::color render_ray(const Ray & ray);

    MultiLightScene(const Point& camera, double screen_width, const Point& screen_center);

    void add_light(const LightSource & src);

};
