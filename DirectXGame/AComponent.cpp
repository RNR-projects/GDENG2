#include "AComponent.h"

AComponent::AComponent(std::string name, ComponentType type, AGameObject* owner) : name(name), type(type), owner(owner)
{
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(AGameObject* owner)
{
    this->owner = owner;
}

void AComponent::detachOwner()
{
    this->owner = nullptr;
}

AGameObject* AComponent::getOwner()
{
    return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
    return this->type;
}

std::string AComponent::getName()
{
    return this->name;
}
