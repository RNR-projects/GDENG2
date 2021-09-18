#include "MenuScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "LoadedMeshObject.h"
#include "Sphere.h"
#include "SceneReader.h"
#include "SceneWriter.h"
#include "Capsule.h"
#include "PhysicsComponent.h"

MenuScreen::MenuScreen() : AUIScreen("Menu")
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open Scene");
	this->openSceneDialog->SetTypeFilters({ ".level" });

	this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	this->saveSceneDialog->SetTitle("Save Scene");
	this->saveSceneDialog->SetTypeFilters({ ".level" });

	SceneReader::initialize();
	SceneWriter::initialize();
}

MenuScreen::~MenuScreen()
{
	SceneWriter::getInstance()->destroy();
	SceneReader::getInstance()->destroy();
	delete this->openSceneDialog;
	delete this->saveSceneDialog;
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) 
	{
		if (ImGui::BeginMenu("File")) 
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) 
			{
				this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) 
			{
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) 
		{
			if (ImGui::MenuItem("Cube")) 
			{ 
				GameObjectManager::getInstance()->addGameObject(new Cube("Cube", Vector3D(), Vector3D(1, 1, 1), Vector3D(), Vector3D())); 
			}
			if (ImGui::MenuItem("Plane")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Plane("Plane", Vector3D(0,-2,0), Vector3D(15, 1, 15), Vector3D(), Vector3D())); 
			}
			if (ImGui::MenuItem("Sphere")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Sphere("Sphere", Vector3D(), 0.5f, 5)); 
			}
			if (ImGui::MenuItem("Capsule")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Capsule("Capsule", Vector3D(), 0.5f, 1)); 
			}
			if (ImGui::MenuItem("CubePhysics")) 
			{ 
				AGameObject* newObject = new Cube("Cube", Vector3D(), Vector3D(1, 1, 1), Vector3D(), Vector3D());
				PhysicsComponent* physics = new PhysicsComponent("physicsComp", newObject);
				physics->addBoxCollider();
				newObject->attachComponent(physics);
				GameObjectManager::getInstance()->addGameObject(newObject); 
			}
			if (ImGui::MenuItem("PlanePhysics")) 
			{
				AGameObject* newObject = new Plane("Plane", Vector3D(0, -2, 0), Vector3D(15, 1, 15), Vector3D(), Vector3D());
				PhysicsComponent* physics = new PhysicsComponent("physicsComp", newObject);
				physics->addBoxCollider();
				physics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
				newObject->attachComponent(physics);
				GameObjectManager::getInstance()->addGameObject(newObject);
			}
			if (ImGui::MenuItem("SpherePhysics")) 
			{
				AGameObject* newObject = new Sphere("Sphere", Vector3D(), 0.5f, 5);
				PhysicsComponent* physics = new PhysicsComponent("physicsComp", newObject);
				physics->addSphereCollider();
				newObject->attachComponent(physics);
				GameObjectManager::getInstance()->addGameObject(newObject);
			}
			if (ImGui::MenuItem("CapsulePhysics")) 
			{
				AGameObject* newObject = new Capsule("Capsule", Vector3D(), 0.5f, 1);
				PhysicsComponent* physics = new PhysicsComponent("physicsComp", newObject);
				physics->addCapsuleCollider();
				newObject->attachComponent(physics);
				GameObjectManager::getInstance()->addGameObject(newObject);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	this->openSceneDialog->Display();
	this->saveSceneDialog->Display();

	if (this->saveSceneDialog->HasSelected())
	{
		SceneWriter::getInstance()->setDirectory(this->saveSceneDialog->GetSelected().string());
		SceneWriter::getInstance()->writeToFile();

		this->saveSceneDialog->ClearSelected();
		this->saveSceneDialog->Close();
	}

	else if (this->openSceneDialog->HasSelected()) 
	{
		SceneReader::getInstance()->setDirectory(this->openSceneDialog->GetSelected().string());
		SceneReader::getInstance()->readFromFile();

		this->openSceneDialog->ClearSelected();
		this->openSceneDialog->Close();
	}
}
