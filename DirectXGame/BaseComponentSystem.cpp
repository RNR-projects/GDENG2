#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
    if (sharedInstance == nullptr)
        BaseComponentSystem::initialize();
    return sharedInstance;
}

void BaseComponentSystem::initialize()
{
    sharedInstance = new BaseComponentSystem();
    sharedInstance->physicsSystem = new PhysicsSystem();
}

void BaseComponentSystem::destroy()
{
    if (sharedInstance != nullptr)
    {
        delete sharedInstance->physicsSystem;
        delete sharedInstance;
    }
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
    return physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
}

BaseComponentSystem::~BaseComponentSystem()
{
}
