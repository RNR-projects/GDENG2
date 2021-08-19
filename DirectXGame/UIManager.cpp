#include "UIManager.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "RenderSystem.h"

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
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //for (int i = 0; i < this->uiList.size(); i++)
    //{
    //    this->uiList[i]->drawUI();
    //}
    //ImGui::ShowDemoWindow();
    ImGui::Begin("Menu", 0, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Color Picker UI")) { isPlaceholderOpen = true; }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits")) { isCreditsOpen = true; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();

    if (isCreditsOpen)
    {
        ImGui::Begin("Credits");
        {
            //ImGui::Image(, ImVec2(100, 100));
            ImGui::Text("Scene Editor v0.1");
            ImGui::Text("Developed by: Robert Nathan Roleda");

            ImGui::Text("Acknowledgements: ");
            ImGui::Text("Sir Neil");
            ImGui::Text("PardCode");
            ImGui::Text("IMGUI");
            ImGui::Text("DirectX");

            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x * 0.5f, ImGui::GetWindowSize().y - 50));
            if (ImGui::Button("Close"))
            {
                isCreditsOpen = false;
            }
        }
        ImGui::End();
    }

    if (isPlaceholderOpen)
    {
        ImGui::Begin("Color Picker", &isPlaceholderOpen);
        ImGui::ColorEdit4("Color", my_color);
        ImGui::End();
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
}

UIManager::~UIManager()
{
}
