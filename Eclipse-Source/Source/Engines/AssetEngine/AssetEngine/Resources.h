#pragma once

#include "AssetEngine/AssetRegistry.h"

#include "AssetEngine/Managers/TextureManager.h"
#include "AssetEngine/Managers/MaterialManager.h"
#include "AssetEngine/PathManager.h"

namespace Eclipse::Assets
{
	class Resourcess
	{
	public:
		template<typename T>
		static T Get(const char* path);

		static void Update();

	private:
		static inline TextureManager textureManager{};
		static inline MaterialManager materialManager{};
	};

	template<typename T>
	T Resourcess::Get(const char* path)
	{
		std::filesystem::path resolvedPath = path;
		if (std::filesystem::path(path).is_absolute())
		{
			resolvedPath = std::filesystem::relative(path, PathManager::GetAssetDir());
		}

		Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		if (!registry.IsRegistered(path)) return {};

		size_t id = registry.GetIdFromPath(path);

		if constexpr (std::is_same<T, Textures>::value) return std::move(textureManager.Get(id));
		else if  constexpr (std::is_same<T, Materials>::value) return std::move(materialManager.Get(id));
	}
}