#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->objectName = gameObject->getName();
	this->localPosition = gameObject->getLocalPosition();
	this->orientation = gameObject->getLocalRotation();
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

Vector3D EditorAction::getStoredOrientation()
{
    return this->orientation;
}
