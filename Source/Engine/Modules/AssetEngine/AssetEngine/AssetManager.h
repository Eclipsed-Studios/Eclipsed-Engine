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

#include <fstream>
#include "CoreEngine/Files/FileWatcher.h"

namespace Eclipse::Assets
{
	class AssetManager
	{
	public:
		static void ImportAssets(const std::filesystem::path& root, const std::string& key = "Assets");
		static void ImportFile(const AssetMeta& meta);
		static void ImportBundle();

		static void CookAndPackageAssets();

		static void EndFrame();

		static bool IsFileReady(const std::string& path)
		{
			for (int i = 0; i < 5; i++)
			{
				std::fstream file(path, std::ios::in | std::ios::binary);

				if (file.is_open())
					return true;

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}

			return false;
		}

		template<typename T>
		static T Load(GUID guid);

		template<typename T>
		static T LoadDefault(DefaultAssetType assetType);

		static void AddFileChanged(const Editor::FileWatcherEvent& e);
		static void ProcessFileChanges();

	private:
		static bool FileWasChanged(const AssetMeta& meta);

		static inline std::vector<Editor::FileWatcherEvent> fileChanges;
		static inline std::mutex fileChangesMutex;

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