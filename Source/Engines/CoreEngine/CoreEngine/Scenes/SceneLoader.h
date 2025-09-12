#pragma once

#include "AssetManagement/Resources/Scene.h"

#include "Components/Transform2D.h"

#include "rapidjson/rapidjson/document.h"

#include <string>

namespace Eclipse
{
	class SceneLoader
	{
	public:
		static void Save(const char* aPath, Scene& outScene);

	private:
		template<typename T>
		static void SaveComponent(rapidjson::Value& aValue, const T* aComponent);

		//static void LoadComponent(const std::string& compName, rapidjson::Value&)
	};
}