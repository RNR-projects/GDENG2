#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "EngineTime.h"	

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new reactphysics3d::PhysicsCommon();
	reactphysics3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world \n";
	delta = -1;
}

PhysicsSystem::~PhysicsSystem()
{
	this->physicsCommon->destroyPhysicsWorld(this->physicsWorld);
	delete this->physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	if (this->componentTable[component->getName()] != nullptr)
	{
		this->componentTable.erase(component->getName());
		int index = -1;
		for (int i = 0; i < this->componentList.size(); i++)
		{
			if (this->componentList[i] == component)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	PhysicsComponent* comp = this->componentTable[name];
	this->componentTable.erase(name);
	this->componentList.erase(std::remove(componentList.begin(), componentList.end(), comp), componentList.end());
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
	return this->componentTable[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	if (delta == -1)
	{
		delta = 0;
	}
	else
	{
		delta += EngineTime::getDeltaTime();
		while (delta >= timeStep)
		{
			this->physicsWorld->update(timeStep);
			for (int i = 0; i < this->componentList.size(); i++)
			{
				this->componentList[i]->perform(timeStep);
			}
			delta -= timeStep;
		}
	}
}

reactphysics3d::PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

reactphysics3d::PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}
