#pragma once

#include "AssetEngine/AssetRegistry.h"

#include "AssetEngine/Managers/TextureManager.h"
#include "AssetEngine/Managers/MaterialManager.h"
#include "AssetEngine/Managers/PixelShaderManager.h"
#include "AssetEngine/Managers/VertexShaderManager.h"
#include "AssetEngine/Managers/AudioClipManager.h"
#include "AssetEngine/Managers/PrefabManager.h"
#include "CoreEngine/PathManager.h"

namespace Eclipse::Assets
{
	class Resources
	{
	public:
		template<typename T>
		static T Get(const char* path);

		template<typename T>
		static T Get(const size_t& id);

		static void Update();

		static Material GetDefaultMaterial();
		static Texture GetDefaultTexture();
		static VertexShader GetDefaultVS();
		static PixelShader GetDefaultPS();

	private:
		static TextureManager textureManager;
		static MaterialManager materialManager;
		static VertexShaderManager vertexShaderManager;
		static PixelShaderManager pixelShaderManager;
		static AudioClipManager audioClipManager;
		static PrefabManager prefabManager;
	};

	template<typename T>
	T Resources::Get(const char* path)
	{
		std::filesystem::path resolvedPath = path;
		if (std::filesystem::path(path).is_absolute())
		{
			resolvedPath = std::filesystem::relative(path, PathManager::GetAssetDir());
		}

		Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		if (!registry.IsRegistered(path)) return {};

		size_t id = registry.GetIdFromPath(path);

		if constexpr (std::is_same<T, Texture>::value) return std::move(textureManager.Get(id));
		else if  constexpr (std::is_same<T, Material>::value) return std::move(materialManager.Get(id));
		else if  constexpr (std::is_same<T, VertexShader>::value) return std::move(vertexShaderManager.Get(id));
		else if  constexpr (std::is_same<T, PixelShader>::value) return std::move(pixelShaderManager.Get(id));
		else if  constexpr (std::is_same<T, AudioClip>::value) return std::move(audioClipManager.Get(id));
		else if  constexpr (std::is_same<T, Prefab>::value) return std::move(prefabManager.Get(id));
	}

	template<typename T>
	T Resources::Get(const size_t& id)
	{
		Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		if (!registry.IsRegistered(id)) return {};

		if constexpr (std::is_same<T, Texture>::value) return std::move(textureManager.Get(id));
		else if  constexpr (std::is_same<T, Material>::value) return std::move(materialManager.Get(id));
		else if  constexpr (std::is_same<T, VertexShader>::value) return std::move(vertexShaderManager.Get(id));
		else if  constexpr (std::is_same<T, PixelShader>::value) return std::move(pixelShaderManager.Get(id));
		else if  constexpr (std::is_same<T, AudioClip>::value) return std::move(audioClipManager.Get(id));
		else if  constexpr (std::is_same<T, Prefab>::value) return std::move(prefabManager.Get(id));
	}
}