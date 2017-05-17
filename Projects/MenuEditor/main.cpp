#include "MenuEditorApp.h"

int main() {
	
	auto app = new MenuEditorApp();
	app->run("AIE", 1080, 720, false);
	delete app;

	return 0;
}