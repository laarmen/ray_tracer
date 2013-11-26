
#include <cmath>
#include <algorithm>
#include <vector>
#include "screen_vector/color.hpp"
rt::color compose(const rt::color& c1, const rt::color& c2) {
    rt::color inv_c1(255-c1.get_red(), 255-c1.get_green(), 255-c1.get_blue(), 255-c1.get_alpha());
    return rt::color(
        c2.get_red()-std::min(inv_c1.get_red(), c2.get_red()),
        c2.get_green()-std::min(inv_c1.get_green(), c2.get_green()),
        c2.get_blue()-std::min(inv_c1.get_blue(), c2.get_blue())
        );
}

rt::color add(const std::vector<rt::color>& v) {
    double red_inv = 1.0;
    double green_inv = 1.0;
    double blue_inv = 1.0;
    for (std::vector<rt::color>::const_iterator it = v.begin(); it != v.end(); ++it) {
        red_inv *= static_cast<double>(255-it->get_red())/255.;
        green_inv *= static_cast<double>(255-it->get_green())/255.;
        blue_inv *= static_cast<double>(255-it->get_blue())/255.;
    }
    return rt::color(
            ceil(255.*(1.0-red_inv)),
            ceil(255.*(1.0-green_inv)),
            ceil(255.*(1.0-blue_inv))
        );
}
