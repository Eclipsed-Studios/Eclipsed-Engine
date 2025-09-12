#pragma once

#include <unordered_map>
#include <vector>
#include <map>

// ------------- Asset includes ------------------
#include "AssetManagement/Resources.h"
#include "AssetManagement/Exporter/AssetExporter.hpp"

#include "AssetManagement/Loader/AssetLoader.hpp"
#include "AssetManagement/Loader/ResourceLoaderHelper.h"

// ------------- Assets includes ------------------
#include "AssetManagement/Resources/Abstract/AbstractResource.h"
#include "AssetManagement/Resources/Abstract/AbstractShader.h"
#include "AssetManagement/Resources/SpriteSheetAnimation.h"

#include "AssetManagement/Resources/Shaders/Shader.h"

#include "AssetManagement/Resources/AudioClip.h"
#include "AssetManagement/Resources/Material.h"
#include "AssetManagement/Resources/Texture.h"
#include "AssetManagement/Resources/Scene.h"


// ------------- Audio includes ------------------
#include "Audio/AudioManager.h"


// ------------- Component includes ------------------
#include "Components/Base/Component.h"

// ------------- Physics ------------------
#include "Components/Physics/BoxCollider2D.h"
#include "Components/Physics/Collider2D.h"
#include "Components/Physics/PolygonCollider2D.h"
#include "Components/Physics/RigidBody2D.h"
// ------------- Rendering ------------------
#include "Components/Rendering/Camera.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
// ------------- AudioSource ------------------
#include "Components/AudioSource.h"
#include "Components/Transform2D.h"


// ------------- Entity Component System Includes ------------------
#include "ECS/ComponentManager.h"


// ------------- File Includes ------------------
#include "Files/MetaFileRegistry.h"


// ------------- Input Includes ------------------
#include "Input/Input.h"
#include "Input/InputAction.h"
#include "Input/InputMapper.h"
#include "Input/Keycodes.h"


// ------------- Scene Includes ------------------
#include "Input/Input.h"
#include "Input/InputAction.h"

#define LEAN_AND_MEAN
#undef APIENTRY
#include <Windows.h>