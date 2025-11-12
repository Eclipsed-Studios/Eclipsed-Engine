#pragma once

#include <unordered_map>
#include <vector>
#include <map>

//----------- Debug Drawers ------------
#include "GraphicsEngine/OpenGL/DebugDrawers/DebugDrawer.h"

//----------- OpenGL Graphics API Includes ------------
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "GraphicsEngine/OpenGL/UniformVariableManager.h"

//----------- Glad Includes ------------
#include "glad/glad.h"

//----------- GLFW Includes ------------
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "KHR/khrplatform.h"

//----------- General Graphics API Includes ------------
#include "GraphicsEngine/AbstractGraphicsAPI.h"
#include "GraphicsEngine/ShaderCompiler.h"

// #define LEAN_AND_MEAN
// #include <Windows.h>