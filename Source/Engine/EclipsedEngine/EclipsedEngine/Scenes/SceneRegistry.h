#pragma once

#include <string>
#include <vector>

#include "AssetEngine/Core/GUID.h"

namespace Eclipse
{
	struct SceneEntry {
		std::string name;
		Assets::GUID guid;
	};

	class SceneRegistry
	{
	public:
		SceneRegistry();

	public:
		const SceneEntry& GetScene(Assets::GUID guid);
		const SceneEntry& GetScene(const std::string& name);

	private:
		std::vector<SceneEntry> registeredScenes;
	};
}