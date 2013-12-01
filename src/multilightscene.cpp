#include "multilightscene.hpp"
#include "object.hpp"
#include "utils.hpp"

//Computes the color of a ray.
//This is used for the original rays from the camera, but can also be used recursively by an object.
rt::color MultiLightScene::render_ray(const Ray & ray) {
    Object * interceptor = get_interceptor(ray);
    if (!interceptor) {
        return rt::color::BLACK;
    }
    rt::color indirect = interceptor->render_indirect(ray, *this);
    std::vector<rt::color> colors(0);
    for(std::vector<LightSource>::const_iterator it = sources.begin(); it != sources.end(); ++it) {
        colors.push_back(interceptor->render_direct(ray, *this, *it));
    }
    rt::color direct = color_average(colors);
    colors.resize(0);
    colors.push_back(indirect);
    colors.push_back(direct);
    return add(colors);
}

MultiLightScene::MultiLightScene(const Point& camera, double screen_width, const Point& screen_center):
    Scene(LightSource(Point(0, 0, 0), rt::color::BLACK), camera, screen_width, screen_center), sources(0) {}

void MultiLightScene::add_light(const LightSource & src) {
    sources.push_back(src);
}
