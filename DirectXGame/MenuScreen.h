#pragma once
#include "AUIScreen.h"
class MenuScreen : public AUIScreen
{
public:
	MenuScreen();
	~MenuScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;
};

