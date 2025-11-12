#pragma once

#include <unordered_map>
#include <vector>
#include <map>

// ------------- Asset includes ------------------
#include "AssetManagement/Resources.h"

#include "AssetManagement/Loader/AssetLoader.hpp"

// ------------- Assets includes ------------------
#include "AssetManagement/Resources/Abstract/AbstractResource.h"
#include "AssetManagement/Resources/Abstract/AbstractShader.h"
#include "AssetManagement/Resources/SpriteSheetAnimation.h"

#include "AssetManagement/Resources/Shaders/Shader.h"

#include "AssetManagement/Resources/AudioClip.h"
#include "AssetManagement/Resources/Material.h"
#include "AssetManagement/Resources/Texture.h"
#include "AssetManagement/Resources/Scene.h"


// ------------- File Includes ------------------
#include "AssetManagement/MetaFileRegistry.h"

#undef APIENTRY
#include <Windows.h>