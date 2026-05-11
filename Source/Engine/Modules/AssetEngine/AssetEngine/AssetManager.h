#pragma once

#include <filesystem>

#include "Assets/Asset.h"
#include "Assets/AudioAsset.h"
#include "Assets/FontAsset.h"
#include "Assets/MaterialAsset.h"
#include "Assets/PrefabAsset.h"
#include "Assets/TextureAsset.h"
#include "Assets/Shader/PixelShaderAsset.h"
#include "Assets/Shader/VertexShaderAsset.h"

#include "IO/BinaryReader.h"

#include "AssetEngine/Core/EditorAssetDatabase.h"
#include "AssetLoader.h"
#include "CoreEngine/MainSingleton.h"
#include "AssetFactory.h"

namespace Eclipse::Assets
{
	class AssetManager
	{
	public:
		static  void ImportAssets(const std::filesystem::path& path, const std::string& key = "Assets");





		static void EndFrame();






		template<typename T>
		static T Load(GUID guid);

		template<typename T>
		static T LoadDefault(DefaultAssetType assetType);

	private:

	};

	template<typename T>
	inline T AssetManager::Load(GUID guid)
	{
		return AssetFactory::ConstructAsset<T>(AssetLoader::Load<T>(guid));
	}
	template<typename T>
	inline T AssetManager::LoadDefault(DefaultAssetType assetType)
	{
		return AssetFactory::ConstructAsset<T>(AssetLoader::LoadDefaultAsset<T>(assetType));
	}
}