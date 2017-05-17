#include "bouncesimApp.h"

int main() {
	
	auto app = new bouncesimApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}