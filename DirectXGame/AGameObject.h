#pragma once
#include <string>
#include "GameObjectConstants.h"
#include "AComponent.h"
#include <vector>

class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(class ConstantBuffer* cb) = 0;

	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	virtual void setScale(float x, float y, float z);
	virtual void setScale(Vector3D scale);
	Vector3D getLocalScale();

	virtual void setRotation(float x, float y, float z);
	virtual void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	std::string getName();
	void setName(std::string newName);

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(std::string name);
	AComponent* findComponentOfType(AComponent::ComponentType type, std::string name);
	std::vector<AComponent*> getComponentsOfType(AComponent::ComponentType type);

protected:
	virtual void updateVertexLocations() = 0;

	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;

	std::vector<AComponent*> componentList;

	virtual void awake();
};

