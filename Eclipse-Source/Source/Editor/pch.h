#pragma once

#include <Windows.h>

#include "ImGui/imgui.h"

// ------------- Editor ImGui Includes ------------------
#include "Editor/ImGui/imgui_impl.h"

// ------------- Window Includes ------------------
#include "Editor/Windows/WindowTypes/AssetWindow/AssetWindow.h"
#include "Editor/Windows/WindowTypes/SceneWindow.h"
#include "Editor/Windows/WindowTypes/GameWindow.h"
#include "Editor/Windows/WindowTypes/ConsoleWindow.h"
#include "Editor/Windows/WindowTypes/DebugWindow.h"
#include "Editor/Windows/WindowTypes/HierarchyWindow.h"
#include "Editor/Windows/WindowTypes/InputEditorWindow.h"
#include "Editor/Windows/WindowTypes/InspectorWindow.h"
#include "Editor/Windows/WindowTypes/SettingsWindow.h"

// ------------- Window Base Includes ------------------
#include "Editor/Windows/WindowManager.h"
#include "Editor/Windows/WindowRegistry.h"

#include "Editor/Windows/WindowTypes/Window.h"
#include "Editor/Windows/Window_Template.h"

// ------------- Editor Includes ------------------
#include "Editor/Common/DragAndDrop.h"
#include "Editor/Editor.h"