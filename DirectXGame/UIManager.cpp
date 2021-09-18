#include "UIManager.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "RenderSystem.h"
#include "EditorPlayScreen.h"
#include "EditorUndoScreen.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
    if (sharedInstance != nullptr)
        return sharedInstance;
    return nullptr;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager(windowHandle);
    sharedInstance->init();
}

void UIManager::destroy()
{
    if (sharedInstance != nullptr)
        sharedInstance->release();
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++)
    {
        this->uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->m_d3d_device, GraphicsEngine::getInstance()->getRenderSystem()->m_imm_context);

    UINames uiNames;
    ProfilerScreen* profilerScreen = new ProfilerScreen();
    this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
    this->uiList.push_back(profilerScreen);
    
    MenuScreen* menuScreen = new MenuScreen();
    this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
    this->uiList.push_back(menuScreen);

    InspectorScreen* inspectorScreen = new InspectorScreen();
    this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
    this->uiList.push_back(inspectorScreen);

    HierarchyScreen* hierarchyScreen = new HierarchyScreen();
    this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
    this->uiList.push_back(hierarchyScreen);
    
    EditorPlayScreen* editorPlayScreen = new EditorPlayScreen();
    this->uiTable[uiNames.EDITOR_PLAY_SCREEN] = editorPlayScreen;
    this->uiList.push_back(editorPlayScreen);
    
    EditorUndoScreen* editorUndoScreen = new EditorUndoScreen();
    this->uiTable[uiNames.EDITOR_UNDO_SCREEN] = editorUndoScreen;
    this->uiList.push_back(editorUndoScreen);
}

UIManager::~UIManager()
{
}

void UIManager::init()
{

}

void UIManager::release()
{
    for (int i = 0; i < this->uiList.size(); i++)
    {
        delete this->uiList[i];
    }
}
