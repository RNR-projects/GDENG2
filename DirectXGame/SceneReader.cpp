#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "StringUtils.h"
#include "AGameObject.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"

SceneReader* SceneReader::sharedInstance = nullptr;

SceneReader* SceneReader::getInstance()
{
    if (sharedInstance == nullptr)
        SceneReader::initialize();
    return sharedInstance;
}

void SceneReader::initialize()
{
    sharedInstance = new SceneReader();
    sharedInstance->init();
}

void SceneReader::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

void SceneReader::setDirectory(std::string dir)
{
    this->directory = dir;
}

void SceneReader::readFromFile()
{
	std::string fileDir = this->directory + ".level";
	if (this->directory.find(".level") != std::string::npos) {
		fileDir = this->directory;
	}

	std::fstream sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	std::string readLine;

	std::string objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) {
			std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 2) {
			std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) {
			std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) {
			std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			switch (objectType)
			{
			case AGameObject::PrimitiveType::CUBE:
				GameObjectManager::getInstance()->addGameObject(new Cube(objectName, position, scale, Vector3D(), rotation));
				break;
			case AGameObject::PrimitiveType::PLANE:
				GameObjectManager::getInstance()->addGameObject(new Plane(objectName, position, scale, Vector3D(), rotation));
				break;
			case AGameObject::PrimitiveType::SPHERE:
				GameObjectManager::getInstance()->addGameObject(new Sphere(objectName, position, scale.x, 5));
			default:
				break;
			}
		}
	}
}

SceneReader::SceneReader()
{
}

SceneReader::~SceneReader()
{
}

void SceneReader::init()
{
}

void SceneReader::release()
{
}
