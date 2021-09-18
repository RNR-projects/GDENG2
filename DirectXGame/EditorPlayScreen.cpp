#include "EditorPlayScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "EngineBackend.h"
#include "GameObjectManager.h"

EditorPlayScreen::EditorPlayScreen() : AUIScreen("EditorPlayButtons")
{

}

EditorPlayScreen::~EditorPlayScreen()
{
}

void EditorPlayScreen::drawUI()
{
	EngineBackend* backend = EngineBackend::getInstance();
	ImGui::Begin("Scene Play Options");
	ImGui::SameLine();
	if (backend->getMode() == EngineBackend::EditorMode::EDITOR)
	{
		if (ImGui::Button("Play", ImVec2(100, 50))) 
		{ 
			GameObjectManager::getInstance()->saveGameobjectStates();
			backend->playEditor(); 
		}
	}
	else if (backend->getMode() == EngineBackend::EditorMode::PLAY)
	{
		if (ImGui::Button("Stop", ImVec2(100, 50))) 
		{ 
			GameObjectManager::getInstance()->resetGameobjectStates();
			backend->returnToEditor(); 
		}
		if (ImGui::Button("Pause", ImVec2(100, 50))) 
		{ 
			backend->pauseEditor(); 
		}
	}
	else
	{
		if (ImGui::Button("Stop", ImVec2(100, 50))) 
		{ 
			GameObjectManager::getInstance()->resetGameobjectStates();
			backend->returnToEditor(); 
		}
		if (ImGui::Button("Resume", ImVec2(100, 50))) 
		{ 
			backend->playEditor(); 
		}
		if (ImGui::Button("Frame Step", ImVec2(100, 50))) 
		{ 
			backend->startFrameStep(); 
		}
	}
	ImGui::End();
}
