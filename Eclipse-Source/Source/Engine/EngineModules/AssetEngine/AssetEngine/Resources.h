#pragma once

#include "AssetEngine/AssetRegistry.h"

#include "AssetEngine/Managers/TextureManager.h"
#include "AssetEngine/Managers/MaterialManager.h"
#include "AssetEngine/Managers/PixelShaderManager.h"
#include "AssetEngine/Managers/VertexShaderManager.h"
#include "AssetEngine/PathManager.h"

namespace Eclipse::Assets
{
	class Resourcess
	{
	public:
		template<typename T>
		static T Get(const char* path);

		template<typename T>
		static T Get(const size_t& id);

		static void Update();

		static Materials GetDefaultMaterial();
		static Textures GetDefaultTexture();
		static VertexShaders GetDefaultVS();
		static PixelShaders GetDefaultPS();

	private:
		static inline TextureManager textureManager{};
		static inline MaterialManager materialManager{};
		static inline VertexShaderManager vertexShaderManager{};
		static inline PixelShaderManager pixelShaderManager{};
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
		else if  constexpr (std::is_same<T, VertexShaders>::value) return std::move(vertexShaderManager.Get(id));
		else if  constexpr (std::is_same<T, PixelShaders>::value) return std::move(pixelShaderManager.Get(id));
	}

	template<typename T>
	T Resourcess::Get(const size_t& id)
	{
		Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		if (!registry.IsRegistered(id)) return {};

		if constexpr (std::is_same<T, Textures>::value) return std::move(textureManager.Get(id));
		else if  constexpr (std::is_same<T, Materials>::value) return std::move(materialManager.Get(id));
		else if  constexpr (std::is_same<T, VertexShaders>::value) return std::move(vertexShaderManager.Get(id));
		else if  constexpr (std::is_same<T, PixelShaders>::value) return std::move(pixelShaderManager.Get(id));
	}
}