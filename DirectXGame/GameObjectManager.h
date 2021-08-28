#pragma once
#include <vector>

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

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	void init();
	void release();

	std::vector<AGameObject*> gameObjectList;
};

