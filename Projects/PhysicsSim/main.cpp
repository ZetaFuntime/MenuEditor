#include "PhysicsSimApp.h"

int main() {
	
	auto app = new PhysicsSimApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}