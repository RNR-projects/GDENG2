#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->objectName = gameObject->getName();
	this->localPosition = gameObject->getLocalPosition();
	this->orientation = {};
	Vector3D rotation = gameObject->getLocalRotation();
	this->orientation.i = rotation.x;
	this->orientation.j = rotation.y;
	this->orientation.k = rotation.z;
	this->localScale = gameObject->getLocalScale();
}

EditorAction::~EditorAction()
{
}

std::string EditorAction::getOwnerName()
{
    return this->objectName;
}

Vector3D EditorAction::getStorePos()
{
    return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
    return this->localScale;
}

Quaternion EditorAction::getStoredOrientation()
{
    return this->orientation;
}
