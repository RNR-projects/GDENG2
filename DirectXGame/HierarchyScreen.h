#pragma once
#include "AUIScreen.h"
class HierarchyScreen : public AUIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;
};

