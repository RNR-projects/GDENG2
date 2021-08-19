#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"

class UINames
{
public:
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
};

class UIManager
{
public:
	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	std::vector<AUIScreen*> uiList;
	std::unordered_map<std::string, AUIScreen*> uiTable;

	bool isCreditsOpen = false;
	bool isPlaceholderOpen = false;
	float my_color[4];
};

