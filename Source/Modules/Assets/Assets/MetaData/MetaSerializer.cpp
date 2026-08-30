#include "MetaSerializer.h"

#include <iostream>
#include <fstream>

#include "Assets/MetaData/Data/TextureMeta.h"
//#include "Assets/MetaData/Data/AudioMeta.h"

#include "Core/PathManager.h"

#include "Core/SupportedAssets.h"

namespace Eclipse::Assets
{
	bool MetaSerializer::MetaFileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(GetMetaPath(path));
	}

	AssetMeta MetaSerializer::LoadOrCreateMeta(const std::filesystem::path& assetPath)
	{
		AssetMeta meta;

		if (MetaFileExists(assetPath)) meta = LoadMeta(assetPath);
		else meta = CreateMeta(assetPath);

		std::filesystem::path path = PathManager::GetArtifactsPath();

		std::string guidStr = meta.guid.ToString();
		path /= guidStr.substr(0, 2);
		path /= guidStr;

		meta.exportedPath = path;

		return meta;
	}

	AssetMeta MetaSerializer::GetMetaType(const std::filesystem::path& assetPath)
	{
		AssetMeta meta;
		meta.type = GetAssetTypeFromExtension(assetPath.extension().string());
		meta.fullPath = assetPath;

		switch (meta.type)
		{
		case AssetType::Texture:
		{
			meta.AddMetaComponent<TextureMeta>();
			break;
		}

		case AssetType::AudioClip:
		{
			break;
		}

		case AssetType::Unknown:
		case AssetType::Material:
		case AssetType::VertexShader:
		case AssetType::PixelShader:
		case AssetType::Font:
		case AssetType::Prefab:
		default:
			break;
		}

		return meta;
	}

	AssetMeta MetaSerializer::CreateMeta(const std::filesystem::path& assetPath)
	{
		AssetMeta meta = GetMetaType(assetPath);
		meta.guid.Generate();
		meta.fullPath = assetPath;
		meta.type = GetAssetTypeFromExtension(assetPath.extension().string());

		const std::string guidStr = meta.guid.ToString();
		meta.exportedPath = PathManager::GetArtifactsPath() / guidStr.substr(0, 2) / guidStr;

		WriteMetaToFile(assetPath, meta);

		return meta;
	}
	
	AssetMeta MetaSerializer::LoadMeta(const std::filesystem::path& assetPath)
	{
		std::filesystem::path metaPath = GetMetaPath(assetPath);
		std::ifstream _if(metaPath);

		AssetMeta meta = GetMetaType(assetPath);
		meta.LoadFromStream(_if);

		return meta;
	}

	void MetaSerializer::WriteMetaToFile(const std::filesystem::path& assetPath, const AssetMeta& assetMeta)
	{
		std::filesystem::path metaPath = GetMetaPath(assetPath);
		std::ofstream of(metaPath);

		assetMeta.WriteToStream(of);
	}

	std::filesystem::path MetaSerializer::GetMetaPath(const std::filesystem::path& assetPath)
	{
		if (assetPath.extension().string() == ".meta")
		{
			return assetPath;
		}
		else
		{
			return assetPath.generic_string() + ".meta";
		}
	}
}