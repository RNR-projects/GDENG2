#pragma once
class EngineBackend
{
public:
	enum EditorMode
	{
		PLAY = 0, PAUSED = 1, EDITOR = 2
	};

	static EngineBackend* getInstance();
	static void initialize();
	static void destroy();

	EditorMode getMode();

	void playEditor();
	void pauseEditor();
	void returnToEditor();

	bool insideFrameStep();
	void startFrameStep();
	void endFrameStep();

private:
	EngineBackend();
	~EngineBackend();
	EngineBackend(EngineBackend const&) {};
	EngineBackend& operator=(EngineBackend const&) {};
	static EngineBackend* sharedInstance;

	void init();
	void release();

	EditorMode editorMode;

	bool isFrameStepping;
};

