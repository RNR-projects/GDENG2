#include "EngineBackend.h"

EngineBackend* EngineBackend::sharedInstance = nullptr;

EngineBackend* EngineBackend::getInstance()
{
    if (sharedInstance == nullptr)
        EngineBackend::initialize();
    return sharedInstance;
}

void EngineBackend::initialize()
{
    sharedInstance = new EngineBackend();
    sharedInstance->init();
}

void EngineBackend::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

EngineBackend::EditorMode EngineBackend::getMode()
{
    return sharedInstance->editorMode;
}

void EngineBackend::playEditor()
{
    sharedInstance->editorMode = EngineBackend::EditorMode::PLAY;
}

void EngineBackend::pauseEditor()
{
    sharedInstance->editorMode = EngineBackend::EditorMode::PAUSED;
}

void EngineBackend::returnToEditor()
{
    sharedInstance->editorMode = EngineBackend::EditorMode::EDITOR;
}

bool EngineBackend::insideFrameStep()
{
    return sharedInstance->isFrameStepping;
}

void EngineBackend::startFrameStep()
{
    sharedInstance->isFrameStepping = true;
}

void EngineBackend::endFrameStep()
{
    sharedInstance->isFrameStepping = false;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}

void EngineBackend::init()
{
    sharedInstance->isFrameStepping = false;
    sharedInstance->editorMode = EngineBackend::EditorMode::EDITOR;
}

void EngineBackend::release()
{
    delete sharedInstance;
}
