#include "ActionHistory.h"
#include "EngineBackend.h"
#include "EditorAction.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;

ActionHistory* ActionHistory::getInstance()
{
    if (sharedInstance == nullptr)
        ActionHistory::initialize();
    return sharedInstance;
}

void ActionHistory::initialize()
{
    sharedInstance = new ActionHistory();
    sharedInstance->init();
}

void ActionHistory::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

void ActionHistory::recordAction(AGameObject* gameObject, bool isUndo)
{
    if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR)
    {
        EditorAction* editorAction = new EditorAction(gameObject);
        if (!isUndo)
        {
            sharedInstance->actionsPerformed.push(editorAction);
        }
        else
        {
            sharedInstance->actionsCancelled.push(editorAction);
        }
    }
}

bool ActionHistory::hasRemainingUndoActions()
{
    return !sharedInstance->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
    return !sharedInstance->actionsCancelled.empty();
}

EditorAction* ActionHistory::undoAction()
{
    if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) 
    {
        return nullptr;
    }

    if (sharedInstance->hasRemainingUndoActions()) {
        EditorAction* action = sharedInstance->actionsPerformed.top();
        sharedInstance->actionsPerformed.pop();
        return action;
    }
    else 
    {
        return nullptr;
    }
}

EditorAction* ActionHistory::redoAction()
{
    if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) 
    {
        return nullptr;
    }

    if (sharedInstance->hasRemainingRedoActions()) {
        EditorAction* action = sharedInstance->actionsCancelled.top();
        sharedInstance->actionsCancelled.pop();
        return action;
    }
    else 
    {
        return nullptr;
    }
}

void ActionHistory::clear()
{       
    while (sharedInstance->hasRemainingUndoActions()) {
        EditorAction* action = sharedInstance->actionsPerformed.top();
        delete action;
        sharedInstance->actionsPerformed.pop();
    }

    while (sharedInstance->hasRemainingRedoActions()) {
        EditorAction* action = sharedInstance->actionsCancelled.top();
        delete action;
        sharedInstance->actionsCancelled.pop();
    }
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}

void ActionHistory::init()
{
    
}

void ActionHistory::release()
{
    this->clear();
}
