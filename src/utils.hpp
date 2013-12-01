#pragma once

#include "screen_vector/color.hpp"
#include <vector>

rt::color compose(const rt::color& c1, const rt::color& c2);

rt::color add(const std::vector<rt::color>& v);

rt::color color_average(const std::vector<rt::color>& v);
