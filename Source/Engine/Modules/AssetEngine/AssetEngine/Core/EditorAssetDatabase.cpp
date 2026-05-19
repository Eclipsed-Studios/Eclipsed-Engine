#include "EditorAssetDatabase.h"

#include "AssetEngine/Discovery/AssetScanner.h"
#include "AssetEngine/Metadata/MetaSerializer.h"

namespace Eclipse::Assets
{
	void AssetDatabase::ProcessSource(const std::filesystem::path& path, const std::string& key)
	{
		std::vector<AssetCandidate> candidates = AssetScanner::Scan(path);

		for (const AssetCandidate& candidate : candidates)
		{
			sourcePathToKey[path.generic_string()] = key;

			ProcessFile(candidate.fullPath, path);
		}
	}

	const AssetMeta& AssetDatabase::ProcessFile(const std::filesystem::path& path, const std::filesystem::path& root)
	{
		AssetMeta file = MetaSerializer::LoadOrCreateMeta(path);

		guidToAsset[file.guid] = std::move(file);
		fullpathToGuid[path] = file.guid;
		pathToGuid[std::filesystem::relative(path, root)] = file.guid;
		const AssetType type = GetAssetTypeFromExtension(path.extension().string());

		typeToAssets[type].push_back(file.guid);
		sourceToAssets[sourcePathToKey[path.generic_string()]].push_back(file.guid);

		return guidToAsset[file.guid];
	}

	const AssetMeta& AssetDatabase::GetProcessedFile(const std::filesystem::path& path) const
	{
		const auto pathIt = pathToGuid.find(path);
		if (pathIt == pathToGuid.end()) throw std::runtime_error("The path cant be found in the map.");

		const auto guidIt = guidToAsset.find(pathToGuid.at(path));
		if (guidIt == guidToAsset.end()) throw std::runtime_error("The guid cant be found in the map.");

		return guidIt->second;
	}

	const AssetMeta& AssetDatabase::GetProcessedFile(const GUID& guid) const
	{
		const auto it = guidToAsset.find(guid);
		if (it == guidToAsset.end()) throw std::runtime_error("The guid cant be found in the map.");

		return it->second;
	}

	const std::vector<GUID>& AssetDatabase::GetGUIDsFromAssetType(AssetType type) const
	{
		const auto it = typeToAssets.find(type);
		if (it != typeToAssets.end()) return it->second;

		return {};
	}

	AssetMeta& AssetDatabase::GetMetaFromMetaPath(const std::filesystem::path& path)
	{
		AssetMeta file = MetaSerializer::LoadOrCreateMeta(path);

		return GetProcessedFile(file.guid);
	}

	AssetMeta& AssetDatabase::GetProcessedFile(const GUID& guid)
	{
		const auto it = guidToAsset.find(guid);
		if (it == guidToAsset.end()) throw std::runtime_error("The guid cant be found in the map.");

		return it->second;
	}

	GUID AssetDatabase::GetGUIDFromFullPath(const std::filesystem::path& fullpath)
	{
		const auto it = fullpathToGuid.find(fullpath);
		if (it == fullpathToGuid.end()) throw std::runtime_error("The guid cant be found in the map.");

		return it->second;
	}

	const std::vector<GUID>& AssetDatabase::GetGUIDFromSource(const std::string& source)
	{
		const auto it = sourceToAssets.find(source);
		if (it == sourceToAssets.end()) throw std::runtime_error("The guid cant be found in the map.");

		return it->second;
	}

	const std::unordered_map<GUID, AssetMeta, GUIDHash>& AssetDatabase::GetSources() const
	{
		return guidToAsset;
	}
}