#include <iostream>
#include <unistd.h>
#include <cassert>

#include "screen_vector/screen.hpp"
#include "multilightscene.hpp"
#include "lightsource.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "screen_vector/color.hpp"

int main(void)
{
	rt::screen s(1280,1024);
    Sphere s1(Point(0, 4, 10), 4, rt::color(150, 150, 150));
    Sphere s2(Point(2, 3, 20), 2, rt::color(150, 100, 150));
    Sphere s3(Point(6, 13, 20), 4, rt::color(150, 100, 100));
    Plane ground(Point(0, 0, 0), rt::vector(0, 1, 0), rt::color(200, 200, 200));
    Plane wall(Point(0, 0, -30), rt::vector(0, 0, -1), rt::color(150, 150, 150));
    LightSource ls1(Point(0, 80, 50), rt::color(155, 155, 155));
    LightSource ls2(Point(40, 40, 28), rt::color(10, 155, 105));
    LightSource ls3(Point(-30, 60, 30), rt::color(80, 140, 150));

    MultiLightScene sc(Point(0, 3, 80), 4.5, Point(0, 3.5, 68));
    sc.add_object(ground);
    sc.add_object(wall);
    sc.add_object(s1);
    sc.add_object(s2);
    sc.add_object(s3);
    sc.add_light(ls1);
    sc.add_light(ls2);
    sc.add_light(ls3);

	// here the code to draw the pixels...

	while(s.update()) {
        sc.render(s);
	}

	return 0;
}
