#pragma once

#include <Windows.h>

#include "ImGui/imgui.h"

// ------------- Editor ImGui Includes ------------------
#include "Editor/ImGui/imgui_impl.h"

// ------------- Window Includes ------------------
#include "Editor/Windows/AssetWindow.h"
#include "Editor/Windows/SceneWindow.h"
#include "Editor/Windows/GameWindow.h"
#include "Editor/Windows/ConsoleWindow.h"
#include "Editor/Windows/DebugWindow.h"
#include "Editor/Windows/HierarchyWindow.h"
#include "Editor/Windows/InputEditorWindow.h"
#include "Editor/Windows/InspectorWindow.h"
#include "Editor/Windows/SettingsWindow.h"

// ------------- Window Base Includes ------------------
#include "Editor/WindowManager.h"
#include "Editor/WindowRegistry.h"

#include "Editor/Windows/Window.h"
#include "Editor/Windows/Window_Template.h"

// ------------- Editor Includes ------------------
#include "Editor/ComponentRegistry.h"
#include "Editor/DragAndDrop.h"
#include "Editor/Editor.h"