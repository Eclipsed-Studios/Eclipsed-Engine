#include "AssetManager.h"

#include "CoreEngine/MainSingleton.h"
#include "AssetEngine/Core/EditorAssetDatabase.h"

#include "AssetTypes/IAssetType.h"
#include "IO/BinaryWriter.h"

#include "AssetTypeRegistry.h"

namespace Eclipse::Assets
{
	void AssetManager::ImportAssets(const std::filesystem::path& root, const std::string& key)
	{
		if (!MainSingleton::Exists<AssetDatabase>())
		{
			MainSingleton::RegisterInstance<AssetDatabase>();
			AssetTypeRegistry::RegisterTypes();
		}

		Editor::FileWatcher::SubscribeToPath(root, AssetManager::AddFileChanged);

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();
		database.ProcessSource(root, key);

		for (auto& [guid, file] : database.GetSources())
		{
			ImportFile(file);
		}
	}



	void AssetManager::EndFrame()
	{
		ProcessFileChanges();
		// delete makred for delete assets.
	}

	void AssetManager::ImportFile(const AssetMeta& meta)
	{
		if (!FileWasChanged(meta))
			return;

		AssetType assetType = GetAssetTypeFromExtension(meta.fullPath.extension().string());
		IAssetType* type = AssetTypeRegistry::GetType(assetType);
		if (type == nullptr) return; // Type is not supported.

		ImportedData imported = type->Import(meta);
		BinaryWriter writer(meta.guid);

		if (type->NeedsProcessing())
		{
			ProcessedData processed = type->Process(imported);
			type->Serialize(writer, processed);
		}
		else
		{
			type->Serialize(writer, imported);
		}
	}

	void AssetManager::AddFileChanged(const Editor::FileWatcherEvent& e)
	{
		std::lock_guard<std::mutex> lock(fileChangesMutex);
		fileChanges.push_back(e);
	}

	void AssetManager::ProcessFileChanges()
	{
		std::vector<Editor::FileWatcherEvent> localChanges;

		// SNAPSHOT (prevents all iterator/race issues)
		{
			std::lock_guard<std::mutex> lock(fileChangesMutex);
			localChanges = std::move(fileChanges);
			fileChanges.clear();
		}

		AssetDatabase& database =
			MainSingleton::GetInstance<AssetDatabase>();

		for (auto& e : localChanges)
		{
			// optional safety check (file still exists / not mid-write)
			if (!std::filesystem::exists(e.path))
				continue;

			switch ((Editor::EventType)e.action)
			{
			case Editor::EventType::Modified:
			case Editor::EventType::FileAdded:
			{
				if (std::filesystem::path(e.path).extension() == ".meta")
				{
					const AssetMeta& meta =
						database.GetMetaFromMetaPath(e.path);

					ImportFile(meta);
				}
				else
				{
					const AssetMeta& meta =
						database.ProcessFile(e.path, e.root);

					ImportFile(meta);
				}
			}
			break;

			default:
				break;
			}
		}
	}

	bool AssetManager::FileWasChanged(const AssetMeta& meta)
	{
		std::filesystem::path exportedPath = PathManager::GetArtifactsPath();
		std::string guidStr = meta.guid.ToString();

		exportedPath /= guidStr.substr(0, 2);
		exportedPath /= guidStr;

		if (!std::filesystem::exists(exportedPath))
			return true;

		std::filesystem::path metaPath = meta.fullPath;
		metaPath += ".meta";

		auto sourceTime = std::filesystem::last_write_time(meta.fullPath);
		auto exportTime = std::filesystem::last_write_time(exportedPath);

		bool sourceChanged = sourceTime > exportTime;

		bool metaChanged = false;
		if (std::filesystem::exists(metaPath))
		{
			auto metaTime = std::filesystem::last_write_time(metaPath);
			metaChanged = metaTime > exportTime;
		}

		return sourceChanged || metaChanged;
	}
}