#pragma once

#include <filesystem>
#include "AssetTypes/IAssetType.h"

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

#include "CoreEngine/MainSingleton.h"

namespace Eclipse::Assets
{
	class AssetManager
	{
	public:
		template<typename T>
		static T Load(const GUID& guid);


		static Font GetDefaultFont();
		static Material GetDefaultUIMaterial();




		// IFDEF EDITOR
		static  void ImportAssets(const std::filesystem::path& path, const std::string& key = "Assets");

		static void RegisterTypes();

		static  IAssetType* GetType(AssetType assetType);

		static inline std::unordered_map<AssetType, IAssetType*> types;
	};

	template<typename T>
	inline T AssetManager::Load(const GUID& guid)
	{
		BinaryReader reader;

		const AssetMeta& meta = MainSingleton::GetInstance<AssetDatabase>().GetProcessedFile(guid);
		GetType(meta.type)->Load(reader, meta);

		return {};
	}
}