#include "Asteroid_ProjectApp.h"

int main() {
	
	auto app = new Asteroid_ProjectApp();
	app->run("Dank memes for the dreams", 1080, 720, false);
	delete app;

	return 0;
}