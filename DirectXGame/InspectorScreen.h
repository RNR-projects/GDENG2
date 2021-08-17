#pragma once
#include "AUIScreen.h"
class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;
};

