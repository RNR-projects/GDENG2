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
#include <d3d11.h>

class UINames
{
public:
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const std::string EDITOR_PLAY_SCREEN = "EDITOR_PLAY_SCREEN";
	const std::string EDITOR_UNDO_SCREEN = "EDITOR_UNDO_SCREEN";
};

class UIManager
{
public:
	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	void init();
	void release();

	std::vector<AUIScreen*> uiList;
	std::unordered_map<std::string, AUIScreen*> uiTable;
};

