#pragma once


#include "point.hpp"
#include "screen_vector/vector.hpp"

struct Impact {
    Point point;

    // It must be normalized.
    rt::vector normale;

};
