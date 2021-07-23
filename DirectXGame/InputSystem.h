#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void intialize();
	static void destroy();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};
	static InputSystem* sharedInstance;

	std::unordered_set<InputListener*> set_listeners;
	unsigned char key_states[256] = {};
	unsigned char old_key_states[256] = {};

	Point old_mouse_pos;
	bool first_time = true;
};

