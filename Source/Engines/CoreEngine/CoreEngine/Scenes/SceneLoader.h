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
		static void Save(const char* aPath);
		static void Load(const char* aPath);


	private:
		static void LoadComponent(const std::string& componentName, const rapidjson::Value& aValue);

		static void WriteMember(rapidjson::Value& aValue, AbstractReflectedVariable* aReflectedVariable, rapidjson::Document::AllocatorType& alloc);
		static void WriteType(rapidjson::Value& aValue, AbstractReflectedVariable* aReflectedVariable, rapidjson::Document::AllocatorType& alloc);
	};
}