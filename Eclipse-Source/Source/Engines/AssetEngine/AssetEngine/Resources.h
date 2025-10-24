#pragma once

#include "AssetEngine/AssetRegistry.h"

#include "AssetEngine/Managers/TextureManager.h"

namespace Eclipse
{
	class Resourcess
	{
	public:
		template<typename T>
		static T Get(const char* path);

		static void Update();

	private:
		static inline TextureManager textureManager{};
	};

	template<typename T>
	T Resourcess::Get(const char* path)
	{
		Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		if (!registry.IsRegistered(path)) return {};

		size_t id = registry.GetIdFromPath(path);

		if constexpr (std::is_same<T, Textures>::value) return std::move(textureManager.Get(id));
	}
}