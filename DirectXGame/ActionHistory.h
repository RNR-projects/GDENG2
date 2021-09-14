#pragma once
#include <stack>

class EditorAction;
class AGameObject;
class ActionHistory
{
public:
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void recordAction(AGameObject* , bool isUndo);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};
	static ActionHistory* sharedInstance;

	void init();
	void release();

	std::stack<EditorAction*> actionsPerformed;
	std::stack<EditorAction*> actionsCancelled;
};

