#include "AppWindow.h"
#include <random>

int main() {
	srand(time(NULL));
	AppWindow::initialize();
	AppWindow* app = AppWindow::getInstance();
	app->createGraphicsWindow();

	while (app->isRunning()) {
		app->broadcast();
	}

	return 0;
}