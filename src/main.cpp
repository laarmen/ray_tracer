#include <iostream>
#include <unistd.h>
#include <cassert>

#include "screen_vector/screen.hpp"
#include "scene.hpp"
#include "lightsource.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "screen_vector/color.hpp"

int main(void)
{
	rt::screen s(640,480);
    Sphere s1(Point(0, 4, 10), 4, rt::color::WHITE);
    Plane ground(Point(0, 0, 0), rt::vector(0, 1, 0), rt::color(128, 128, 128));
    Plane wall(Point(0, 0, 30), rt::vector(0, 0, 1), rt::color(128, 128, 128));
    LightSource ls(Point(-20, 80, -80), rt::color::WHITE);

    Scene sc(ls, Point(0, 3, -3), 4, Point(0, 3, 0));
    sc.add_object(ground);
    sc.add_object(wall);
    sc.add_object(s1);

	// here the code to draw the pixels...

	while(s.update()) {
        sc.render(s);
	}

	return 0;
}
