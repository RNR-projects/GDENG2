#include "EditorUndoScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "EngineBackend.h"
#include "ActionHistory.h"
#include "GameObjectManager.h"

EditorUndoScreen::EditorUndoScreen() : AUIScreen("EditorUndoScreen")
{
}

EditorUndoScreen::~EditorUndoScreen()
{
}

void EditorUndoScreen::drawUI()
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR)
	{
		ImGui::Begin("Actions");
		ImGui::SameLine();
		if (ImGui::Button("Undo", ImVec2(100, 50)))
		{
			if (ActionHistory::getInstance()->hasRemainingUndoActions())
				GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction(), true);
		}
		if (ImGui::Button("Redo", ImVec2(100, 50)))
		{
			if (ActionHistory::getInstance()->hasRemainingRedoActions())
				GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction(), false);
		}
		ImGui::End();
	}
}
