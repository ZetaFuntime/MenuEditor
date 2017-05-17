#include "SceneGraphApp.h"

int main() {
	
	auto app = new SceneGraphApp();
	app->run("AIE", 1900, 980, false);
	delete app;

	return 0;
}