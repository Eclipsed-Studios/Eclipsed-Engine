#pragma once

#include "EntityEngine/Components/Transform2D.h"

#include "rapidjson/rapidjson/document.h"

#include <string>

namespace Eclipse
{
	namespace Reflection
	{
		class AbstractSerializedVariable;
	}

	class SceneLoader
	{
	public:
		static void Save(const char* aPath);
		static void Load(const char* aPath);

		static void WriteMember(rapidjson::Value& aValue, Reflection::AbstractSerializedVariable* aSerializedVariable, rapidjson::Document::AllocatorType& alloc);
		static void LoadComponent(const std::string& componentName, const rapidjson::Value& aValue);
	private:
		static void LoadType(Reflection::AbstractSerializedVariable* aSerializedVariable, const rapidjson::Value& aValue);

	};
}