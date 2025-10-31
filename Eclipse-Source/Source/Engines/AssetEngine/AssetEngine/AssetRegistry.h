#pragma once

#include <filesystem>
#include <unordered_map>

#include "AssetEngine/Models/AssetRegistryEntry.h"
#include "AssetEngine/Models/AssetType.h"

namespace Eclipse::Assets
{
	class AssetRegistry final
	{
	public:
		static AssetRegistry& GetInstance();

	private:
		AssetRegistry() = default;
		~AssetRegistry() = default;

	public:
		void RegisterAsset(const std::filesystem::path& fullPath, const std::filesystem::path& relativePath, AssetType type);
		void UnregisterAsset(const size_t& id);

		const AssetRegistryEntry& GetRegisteredAsset(const size_t& id);
		const AssetRegistryEntry& GetRegisteredAsset(const std::filesystem::path& path);
		const std::unordered_map<size_t, AssetRegistryEntry>& GetRegisteredAssets();

		bool IsRegistered(const size_t& id);
		bool IsRegistered(const std::filesystem::path& path);

		size_t GetIdFromPath(const std::filesystem::path& path);

		std::filesystem::path ResolvePath(const std::filesystem::path& path) const;

		void Load();
		void Save();

	private:
		std::unordered_map<AssetType, std::vector<size_t>> assetTypeToID;
		std::unordered_map<size_t, AssetRegistryEntry> registeredAssets;

		static inline std::filesystem::path metafilePath;
	};
}