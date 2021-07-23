#include "AppWindow.h"

int main() {
	AppWindow::initialize();
	AppWindow* app = AppWindow::getInstance();
	app->createGraphicsWindow();

	while (app->isRunning()) {
		app->broadcast();
	}

	return 0;
}