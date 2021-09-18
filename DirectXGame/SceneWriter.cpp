#include "SceneWriter.h"
#include <fstream>
#include <iostream>
#include "GameObjectManager.h"
#include "AGameObject.h"
#include "Sphere.h"
#include "Capsule.h"

SceneWriter* SceneWriter::sharedInstance = nullptr;

SceneWriter* SceneWriter::getInstance()
{
    if (sharedInstance == nullptr)
        SceneWriter::initialize();
    return sharedInstance;
}

void SceneWriter::initialize()
{
    sharedInstance = new SceneWriter();
    sharedInstance->init();
}

void SceneWriter::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

void SceneWriter::setDirectory(std::string dir)
{
    this->directory = dir;
}

void SceneWriter::writeToFile()
{
    std::string fileDir = this->directory + ".level";
    if (this->directory.find(".level") != std::string::npos)
    {
        fileDir = this->directory;
    }

    std::fstream sceneFile;
    sceneFile.open(fileDir, std::ios::out);

    std::cout << "Selected filename " << fileDir << "\n";

    std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllObjects();

    for (int i = 0; i < allObjects.size(); i++)
    {
        sceneFile << allObjects[i]->getName() << std::endl;
        Vector3D pos = allObjects[i]->getLocalPosition();
        Vector3D rot = allObjects[i]->getLocalRotation();
        Vector3D scale = allObjects[i]->getLocalScale();

        sceneFile << "Type: " << allObjects[i]->getObjectType() << std::endl;
        sceneFile << "Position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
        sceneFile << "Rotation: " << rot.x << " " << rot.y << " " << rot.z << std::endl;
        sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;

        if (allObjects[i]->findComponentByName("physicsComp") != nullptr)
        {
            sceneFile << "HasRigidBody: " << 1 << std::endl;
        }
        else
        {
            sceneFile << "HasRigidBody: " << 0 << std::endl;
        }
    }
    sceneFile.close();
}

SceneWriter::SceneWriter()
{
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::init()
{
}

void SceneWriter::release()
{
    delete sharedInstance;
}
