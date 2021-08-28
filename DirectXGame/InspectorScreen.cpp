#include "InspectorScreen.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include "AGameObject.h"

InspectorScreen::InspectorScreen() : AUIScreen("Inspector")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	selectedObject = GameObjectManager::getInstance()->getSelectedObject();
	if (selectedObject != nullptr) {
		std::string name = selectedObject->getName();
		ImGui::Text("Selected Object: %s", name.c_str());

		Vector3D position = selectedObject->getLocalPosition();
		Vector3D rotation = selectedObject->getLocalRotation();
		Vector3D objectScale = selectedObject->getLocalScale();

		pos[0] = position.x;
		pos[1] = position.y;
		pos[2] = position.z;
		
		rot[0] = rotation.x;
		rot[1] = rotation.y;
		rot[2] = rotation.z;
		
		scale[0] = objectScale.x;
		scale[1] = objectScale.y;
		scale[2] = objectScale.z;

		if (ImGui::InputFloat3("Position", pos)) { updatePosition(); }
		if (ImGui::InputFloat3("Rotation", rot)) { updateRotation(); }
		if (ImGui::InputFloat3("Scale", scale)) { updateScale(); }

	}
	ImGui::End();
}

void InspectorScreen::updatePosition()
{
	if (selectedObject != nullptr)
		selectedObject->setPosition(Vector3D(pos[0], pos[1], pos[2]));
}

void InspectorScreen::updateRotation()
{
	if (selectedObject != nullptr)
		selectedObject->setRotation(Vector3D(rot[0], rot[1], rot[2]));
}

void InspectorScreen::updateScale()
{
	if (selectedObject != nullptr)
		selectedObject->setScale(Vector3D(scale[0], scale[1], scale[2]));
}
