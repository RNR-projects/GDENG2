#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Sphere.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner, bool isSphere) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
    BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
    reactphysics3d::PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

    reactphysics3d::Transform transform;
    Vector3D rot = this->getOwner()->getLocalRotation();
    reactphysics3d::Quaternion quat = reactphysics3d::Quaternion::fromEulerAngles(rot.x, rot.y, rot.z);
    transform.setOrientation(quat);
    Vector3D pos = this->getOwner()->getLocalPosition();
    transform.setPosition(reactphysics3d::Vector3(pos.x, pos.y, pos.z));
    Vector3D scale = this->getOwner()->getLocalScale();
    if (!isSphere)
    {
        reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.x / 2, scale.y / 2, scale.z / 2));
        this->rigidBody = physicsWorld->createRigidBody(transform);
        transform.setToIdentity();
        this->rigidBody->addCollider(boxShape, transform);
    }
    else
    {
        reactphysics3d::SphereShape* sphereShape = physicsCommon->createSphereShape(((Sphere*)this->getOwner())->getRadius());
        this->rigidBody = physicsWorld->createRigidBody(transform);
        transform.setToIdentity();
        this->rigidBody->addCollider(sphereShape, transform);
    }
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
}

PhysicsComponent::~PhysicsComponent()
{
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
    physicsWorld->destroyRigidBody(this->rigidBody);
}

void PhysicsComponent::perform(float deltaTime)
{
    if (rigidBody->getType() != reactphysics3d::BodyType::STATIC)
    {
        const reactphysics3d::Transform transform = this->rigidBody->getTransform();
        reactphysics3d::Vector3 newPos;
        reactphysics3d::Quaternion newRot;
        newPos = transform.getPosition();
        newRot = transform.getOrientation();

        this->getOwner()->setRotation(Quaternion::toEuler(Quaternion(newRot.w, newRot.x, newRot.y, newRot.z)));
        this->getOwner()->setPosition(newPos.x, newPos.y, newPos.z);
    }
}

reactphysics3d::RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidBody;
}
