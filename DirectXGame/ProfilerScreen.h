#pragma once
#include "AUIScreen.h"
class ProfilerScreen : public AUIScreen
{
public:
	ProfilerScreen();
	~ProfilerScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;
};

