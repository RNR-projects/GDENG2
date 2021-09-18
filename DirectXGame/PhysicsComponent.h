#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(std::string name, AGameObject* owner);
	~PhysicsComponent();

	void addSphereCollider();
	void addBoxCollider();
	void addCapsuleCollider();

	void perform(float deltaTime) override;
	reactphysics3d::RigidBody* getRigidBody();

	void resetTransform();

private:
	float mass = 1.0f;
	reactphysics3d::RigidBody* rigidBody;
};

