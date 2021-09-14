#pragma once
#include <string>

class SceneReader
{
public:
	static SceneReader* getInstance();
	static void initialize();
	static void destroy();

	void setDirectory(std::string dir);
	void readFromFile();

private:
	SceneReader();
	~SceneReader();
	SceneReader(SceneReader const&) {};
	SceneReader& operator=(SceneReader const&) {};
	static SceneReader* sharedInstance;

	void init();
	void release();

	std::string directory;
};

