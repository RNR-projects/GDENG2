#pragma once
#include "AUIScreen.h"

class EditorPlayScreen : public AUIScreen
{
public:
	EditorPlayScreen();
	~EditorPlayScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;
};

