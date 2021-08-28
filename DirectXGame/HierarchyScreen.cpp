#include "HierarchyScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include <string>

HierarchyScreen::HierarchyScreen() : AUIScreen("Hierarchy")
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Scene Outliner");
	std::vector<std::string> gameObjectNames = GameObjectManager::getInstance()->getGameObjectNames();
	for (int i = 0; i < gameObjectNames.size(); i++)
	{
		if (ImGui::Button(gameObjectNames[i].c_str(), ImVec2(200, 0))) {
			GameObjectManager::getInstance()->selectObject(i);
		}
	}
	ImGui::End();
}
