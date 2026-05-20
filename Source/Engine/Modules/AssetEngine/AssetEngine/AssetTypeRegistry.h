#pragma once

#include <unordered_map>
#include "Core/SupportedAssets.h"

#include "AssetEngine/Assets/AudioAsset.h"
#include "AssetEngine/Assets/FontAsset.h"
#include "AssetEngine/Assets/MaterialAsset.h"
#include "AssetEngine/Assets/PrefabAsset.h"
#include "AssetEngine/Assets/SceneAsset.h"
#include "AssetEngine/Assets/TextureAsset.h"
#include "AssetEngine/Assets/Shader/PixelShaderAsset.h"
#include "AssetEngine/Assets/Shader/VertexShaderAsset.h"

namespace Eclipse::Assets
{
	class IAssetType;
	class AssetTypeRegistry
	{
	public:
		static void RegisterTypes();

		static  IAssetType* GetType(AssetType assetType);

		template<typename T>
		static IAssetType* GetType();

	private:
		static inline std::unordered_map<AssetType, IAssetType*> types;
	};

	template<typename T>
	inline IAssetType* AssetTypeRegistry::GetType()
	{
		if constexpr (std::is_same<T, AudioClip>::value)return types[AssetType::AudioClip];
		else if constexpr (std::is_same<T, Font>::value)return types[AssetType::Texture];
		else if constexpr (std::is_same<T, Material>::value)return types[AssetType::Material];
		else if constexpr (std::is_same<T, Prefab>::value)return types[AssetType::Prefab];
		else if constexpr (std::is_same<T, VertexShader>::value)return types[AssetType::VertexShader];
		else if constexpr (std::is_same<T, PixelShader>::value)return types[AssetType::PixelShader];
		else if constexpr (std::is_same<T, Texture>::value)return types[AssetType::Texture];
		else if constexpr (std::is_same<T, Scene>::value)return types[AssetType::Scene];

		return nullptr;
	}
}