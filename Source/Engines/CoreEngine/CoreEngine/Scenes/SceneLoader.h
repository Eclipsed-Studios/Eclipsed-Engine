#pragma once

#include "AssetManagement/Resources/Scene.h"

#include "Components/Transform2D.h"

#include "rapidjson/rapidjson/document.h"

namespace Eclipse
{
	class SceneLoader
	{
	public:
		static void Save(const char* aPath, Scene& outScene);
	};
}