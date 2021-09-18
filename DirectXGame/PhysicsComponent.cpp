#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Sphere.h"
#include "Capsule.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
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
    this->rigidBody = physicsWorld->createRigidBody(transform);
}

PhysicsComponent::~PhysicsComponent()
{
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
    physicsWorld->destroyRigidBody(this->rigidBody);
    BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
    AComponent::~AComponent();
}

void PhysicsComponent::addSphereCollider()
{
    reactphysics3d::PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
    reactphysics3d::Transform transform;

    reactphysics3d::SphereShape* shape = physicsCommon->createSphereShape(((Sphere*)this->getOwner())->getRadius() * this->getOwner()->getLocalScale().x);
    transform.setToIdentity();
    this->rigidBody->addCollider(shape, transform);
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
}

void PhysicsComponent::addBoxCollider()
{
    reactphysics3d::PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
    Vector3D scale = this->getOwner()->getLocalScale();
    reactphysics3d::Transform transform;

    reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.x / 2.0f, scale.y / 2.0f, scale.z / 2.0f));
    transform.setToIdentity();
    this->rigidBody->addCollider(boxShape, transform);
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
}

void PhysicsComponent::addCapsuleCollider()
{
    reactphysics3d::PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
    reactphysics3d::Transform transform;

    reactphysics3d::CapsuleShape* shape = physicsCommon->createCapsuleShape(((Capsule*)this->getOwner())->getRadius() * this->getOwner()->getLocalScale().x, 
        ((Capsule*)this->getOwner())->getCylinderHeight() * this->getOwner()->getLocalScale().y);
    transform.setToIdentity();
    this->rigidBody->addCollider(shape, transform);
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
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

void PhysicsComponent::resetTransform()
{
    reactphysics3d::Transform transform;
    Vector3D rot = this->getOwner()->getLocalRotation();
    reactphysics3d::Quaternion quat = reactphysics3d::Quaternion::fromEulerAngles(rot.x, rot.y, rot.z);
    transform.setOrientation(quat);
    Vector3D pos = this->getOwner()->getLocalPosition();
    transform.setPosition(reactphysics3d::Vector3(pos.x, pos.y, pos.z));
    this->rigidBody->setTransform(transform);
    this->rigidBody->setLinearVelocity({ 0,0,0 });
    this->rigidBody->setAngularVelocity({ 0,0,0 });
}
