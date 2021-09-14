#pragma once
#include "AUIScreen.h"
class EditorUndoScreen : public AUIScreen
{
public:
	EditorUndoScreen();
	~EditorUndoScreen();

	virtual void drawUI() override;
};

