#include "MenuScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "LoadedMeshObject.h"

MenuScreen::MenuScreen() : AUIScreen("Menu")
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {  }
			if (ImGui::MenuItem("Save", "Ctrl+S")) {  }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Cube")) 
			{ 
				GameObjectManager::getInstance()->addGameObject(new Cube("Cube", Vector3D(), Vector3D(1, 1, 1), Vector3D(), Vector3D())); 
			}
			if (ImGui::MenuItem("Plane")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Plane("Plane", Vector3D(0,-1,0), Vector3D(5, 1, 5), Vector3D(), Vector3D())); 
			}
			if (ImGui::MenuItem("Teapot")) 
			{
				GameObjectManager::getInstance()->addGameObject(new LoadedMeshObject("Teapot", Vector3D(), Vector3D(1, 1, 1), Vector3D(), L"Assets\\Meshes\\teapot.obj"));
			}
			if (ImGui::MenuItem("Armadillo")) 
			{
				GameObjectManager::getInstance()->addGameObject(new LoadedMeshObject("Armadillo", Vector3D(), Vector3D(1, 1, 1), Vector3D(), L"Assets\\Meshes\\armadillo.obj"));
			}
			if (ImGui::MenuItem("Bunny"))
			{
				GameObjectManager::getInstance()->addGameObject(new LoadedMeshObject("Bunny", Vector3D(), Vector3D(1, 1, 1), Vector3D(), L"Assets\\Meshes\\bunny.obj"));
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
