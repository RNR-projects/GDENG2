#pragma once
#include <string>

class SceneWriter
{
public:
	static SceneWriter* getInstance();
	static void initialize();
	static void destroy();

	void setDirectory(std::string dir);
	void writeToFile();

private:
	SceneWriter();
	~SceneWriter();
	SceneWriter(SceneWriter const&) {};
	SceneWriter& operator=(SceneWriter const&) {};
	static SceneWriter* sharedInstance;

	void init();
	void release();

	std::string directory;
};

