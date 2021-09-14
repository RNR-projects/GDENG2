#include "GameObjectManager.h"
#include "AGameObject.h"
#include "EditorAction.h"
#include "ActionHistory.h"

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
    if (findObjectByName(gameObject->getName()) != nullptr) 
    {
        int count = 1;
        std::string revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
        while (findObjectByName(revisedString) != nullptr) 
        {
            count++;
            revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
        }
        gameObject->setName(revisedString);
        gameObjectNames.push_back(revisedString);
    }
    else 
    {
        gameObjectNames.push_back(gameObject->getName());
    }
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

std::vector<std::string> GameObjectManager::getGameObjectNames()
{
    return gameObjectNames;
}

std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
    return gameObjectList;
}

void GameObjectManager::selectObject(int index)
{
    selectedObject = gameObjectList[index];
}

void GameObjectManager::selectObject(AGameObject* gameObject)
{
    selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
    return selectedObject;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
    for (int i = 0; i < gameObjectNames.size(); i++)
    {
        if (gameObjectNames[i] == name)
        {
            return gameObjectList[i];
        }
    }
    return nullptr;
}

void GameObjectManager::applyEditorAction(EditorAction* action, bool isUndo)
{
    AGameObject* object = this->findObjectByName(action->getOwnerName());
    if (object != nullptr) 
    {
        ActionHistory::getInstance()->recordAction(object, isUndo);

        object->setPosition(action->getStorePos());
        object->setRotation(action->getStoredOrientation());
        object->setScale(action->getStoredScale());
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
