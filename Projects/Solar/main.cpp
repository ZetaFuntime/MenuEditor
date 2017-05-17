#define _USE_MATH_DEFINES

#include "SolarApp.h"
#include <iostream>
#include <math.h>

int main() {
	auto app = new SolarApp();
	app->run("Solar System", 1280, 720, false);
	delete app;

	return EXIT_SUCCESS;
}