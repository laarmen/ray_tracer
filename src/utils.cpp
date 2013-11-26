
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
    double red_sum = 0;
    double green_sum = 0;
    double blue_sum = 0;
    for (std::vector<rt::color>::const_iterator it = v.begin(); it != v.end(); ++it) {
        red_sum += pow(static_cast<double>(it->get_red()), 2);
        green_sum += pow(static_cast<double>(it->get_green()), 2);
        blue_sum += pow(static_cast<double>(it->get_blue()), 2);
    }
    ;
    return rt::color(ceil(sqrt(red_sum/v.size())),
            ceil(sqrt(green_sum/v.size())),
            ceil(sqrt(blue_sum/v.size()))
        );
}
