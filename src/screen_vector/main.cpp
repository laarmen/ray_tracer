#include <iostream>
#include <unistd.h>

#include "screen.hpp"

int main(void)
{
	rt::screen s(640,480);

	// here the code to draw the pixels...

	while(s.update()) {
		// wait for an input from user
	}

	return 0;
}
