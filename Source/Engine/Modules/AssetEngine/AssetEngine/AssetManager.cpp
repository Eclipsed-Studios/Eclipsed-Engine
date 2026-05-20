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

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();

		Editor::FileWatcher::SubscribeToPath(root, AssetManager::AddFileChanged);

		database.ProcessSource(root, key);

		for (auto& [guid, file] : database.GetSources())
		{
			ImportFile(file);
		}
	}



	void AssetManager::EndFrame()
	{
#ifdef ECLIPSED_EDITOR
		ProcessFileChanges();
#endif
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

	void AssetManager::ImportBundle()
	{
		if (!MainSingleton::Exists<AssetDatabase>())
		{
			MainSingleton::RegisterInstance<AssetDatabase>();
			AssetTypeRegistry::RegisterTypes();
		}

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();
		database.ProcessBundle("packed_file.bundle");
	}

	void AssetManager::PackAssets()
	{
		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();

		std::ofstream out(PathManager::GetProjectRoot() / "Build/packed_file.bundle", std::ios::binary);

		std::vector<Assets::GUID> guids;
		for (auto& [guid, file] : database.GetSources())
		{
			guids.push_back(guid);
		}

		size_t size = guids.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

		struct Header {
			Assets::GUID guid;
			size_t size;
			size_t offset;
			AssetType type;
			char name[32];
		};

		size_t offset = sizeof(size_t) + sizeof(Header) * size;
		for (const Assets::GUID& guid : guids)
		{
			const Assets::AssetMeta& meta = database.GetProcessedFile(guid);
			const size_t fileSize = std::filesystem::file_size(meta.exportedPath);

			Header header;/* = { guid, fileSize, offset, meta.type, meta.fullPath.filename().stem().string().c_str() };*/

			header.guid = guid;
			header.size = fileSize;
			header.offset = offset;
			header.type = meta.type;

			std::string fileName = meta.fullPath.filename().stem().string();
			strncpy(header.name, fileName.c_str(), 32);
			header.name[sizeof(header.name) - 1] = '\0';

			out.write(reinterpret_cast<const char*>(&header), sizeof(Header));

			offset += fileSize;
		}

		for (const Assets::GUID& guid : guids)
		{
			const Assets::AssetMeta& meta = database.GetProcessedFile(guid);
			const size_t fileSize = std::filesystem::file_size(meta.exportedPath);

			std::ifstream file(meta.exportedPath, std::ios::binary);
			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string content = buffer.str();

			out.write(content.data(), content.size());
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