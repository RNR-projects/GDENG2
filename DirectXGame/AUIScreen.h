#pragma once
#include <string>

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	virtual ~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	std::string name;

	friend class UIManager;
};

