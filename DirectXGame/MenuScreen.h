#pragma once
#include "AUIScreen.h"
#include "IMGUI/imfilebrowser.h"

class MenuScreen : public AUIScreen
{
public:
	MenuScreen();
	~MenuScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;

private:

	ImGui::FileBrowser* saveSceneDialog;
	ImGui::FileBrowser* openSceneDialog;
};

