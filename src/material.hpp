#pragma once

#include "screen_vector/color.hpp"

class Impact;
class Scene;
class LightSource;
class Ray;

class Material {
    public:
        virtual rt::color indirect_rendering(const Ray & ray, Scene & scene, const Impact & impact, Object & obj) = 0;
        virtual rt::color direct_rendering(const Ray & ray, Scene & scene, const LightSource & light_source, const Impact & impact, Object & obj) = 0;
};
