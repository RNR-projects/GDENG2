#include "GameObjectManager.h"
#include "AGameObject.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
    if (sharedInstance == nullptr)
        GameObjectManager::initialize();
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    sharedInstance = new GameObjectManager();
    sharedInstance->init();
}

void GameObjectManager::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

void GameObjectManager::addGameObject(AGameObject* gameObject)
{
    gameObjectList.push_back(gameObject);
}

void GameObjectManager::updateAllGameObjects(float deltaTime)
{
    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->update(deltaTime);
    }
}

void GameObjectManager::drawAllGameObjects(ConstantBuffer* cb)
{
    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->draw(cb);
    }
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::init()
{
}

void GameObjectManager::release()
{
    for (int i = 0; i < gameObjectList.size(); i++)
    {
        delete gameObjectList[i];
    }
    gameObjectList.clear();
}
