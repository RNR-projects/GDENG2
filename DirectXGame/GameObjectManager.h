#pragma once
#include <vector>
#include <string>

class AGameObject;
class ConstantBuffer;
class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	void addGameObject(AGameObject* gameObject);

	void updateAllGameObjects(float deltaTime);
	void drawAllGameObjects(ConstantBuffer* cb);

	std::vector<std::string> getGameObjectNames();

	void selectObject(int index);
	void selectObject(AGameObject* gameObject);

	AGameObject* getSelectedObject();

	AGameObject* findObjectByName(std::string name);

	void applyEditorAction(class EditorAction* action, bool isUndo);

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	void init();
	void release();

	std::vector<AGameObject*> gameObjectList;
	std::vector<std::string> gameObjectNames;

	AGameObject* selectedObject = nullptr;
};

