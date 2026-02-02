//#include "AssetEngine/Editor/Importer/TypeImporters/EditorAudioImporter.h"
//
//#include "AssetEngine/Editor/MetaFile/AssetMetaManager.h"
//#include "AssetEngine/Editor/MetaFile/MetaFileRegistry.h"
//#include "AssetEngine/Editor/GUID/GuidGenerator.h"
//
//#include "AssetEngine/Editor/Importer/ImportSettings/AssetImportSettings.h"
//
//#include <fstream>
//#include <cereal/archives/json.hpp>
//
//#include "AssetEngine/Data/AudioData.h"
//#include "AssetEngine/SupportedTypes.h"
//
//namespace Eclipse
//{
//	void AudioImporter::Import(const std::filesystem::path& aPath)
//	{
//		std::filesystem::path metaFilePath = aPath;
//		if (aPath.extension() != ".meta")
//		{
//			metaFilePath = MetaFileRegistry::CreateMetaFile(aPath);
//		}
//
//		GUID guid = GuidGenerator::Generate();
//		 
//		AssetMetaSettings settings;
//		settings.guid = guid;
//
//		{ // Exporting
//			AudioClipData data;
//			{
//
//			}
//
//			std::filesystem::path exportFolderPath = path / "Artifacts" / guid.substr(0, 2);
//			std::filesystem::create_directories(exportFolderPath);
//
//			std::filesystem::path exportedPath = exportFolderPath / guid;
//			std::ofstream exported(exportedPath, std::ios::binary);
//
//			int type = (int)AssetType::AudioClip;
//			exported.write(reinterpret_cast<const char*>(&type), sizeof(int));
//		}
//
//		std::ofstream metafile(metaFilePath);
//		cereal::JSONOutputArchive ar(metafile);
//		ar(settings);
//	}
//
//	void AudioImporter::Reimport(const std::filesystem::path& aPath)
//	{
//		std::filesystem::path metaFilePath = aPath;
//		if (aPath.extension() != ".meta")
//		{
//			metaFilePath = MetaFileRegistry::GetMetaFilePath(aPath);
//		}
//
//		std::ifstream in(metaFilePath);
//		AssetMetaSettings settings;
//		cereal::JSONInputArchive ar(in);
//		ar(settings);
//
//		{ // Exporting
//			AudioClipData data;
//			{
//
//			}
//
//			std::filesystem::path exportFolderPath = path / "Artifacts" / settings.guid.substr(0, 2);
//			std::filesystem::create_directories(exportFolderPath);
//
//			std::filesystem::path exportedPath = exportFolderPath / settings.guid;
//			std::ofstream exported(exportedPath, std::ios::binary);
//
//			int type = (int)AssetType::AudioClip;
//			exported.write(reinterpret_cast<const char*>(&type), sizeof(int));
//		}
//	}
//}