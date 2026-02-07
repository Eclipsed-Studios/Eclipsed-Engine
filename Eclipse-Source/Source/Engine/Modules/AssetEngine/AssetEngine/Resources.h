#pragma once

#include "AssetEngine/Runtime/Managers/AssetManager.h"
#include "AssetEngine/SupportedTypes.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace Eclipse
{
	class Resources {
	public:
		template<typename T>
		static T Get(const std::string& aGuid);

		template<typename T>
		static T GetDefault();

	private:
		static VertexShaderManager vertexShaderManager;
		static PixelShaderManager pixelShaderManager;
		static MaterialManager materialManager;
		static TextureManager textureManager;
		static PrefabManager prefabManager;
	};

	template<typename T>
	inline T Resources::Get(const std::string& aGuid)
	{
		if (aGuid.empty()) return {};

		std::filesystem::path exportFolderPath = PathManager::GetArtifactsPath() / aGuid.substr(0, 2) / aGuid;

		std::ifstream in(exportFolderPath, std::ios::binary);

		AssetType type = AssetType::Unknown;
		in.read(reinterpret_cast<char*>(&type), sizeof(int));

		if constexpr (std::is_same<T, Texture>::value) return textureManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, VertexShader>::value) return vertexShaderManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, PixelShader>::value) return pixelShaderManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, Material>::value) return materialManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, Prefab>::value) return prefabManager.Get(aGuid, in);
	}

	template<typename T>
	inline T Resources::GetDefault()
	{
		if constexpr (std::is_same<T, Material>::value)
		{
			std::string guid = "77bec88f8a2d7fe866935e09c69000ab";

			std::filesystem::path exportFolderPath = PathManager::GetArtifactsPath() / guid.substr(0, 2) / guid;
			std::ifstream in(exportFolderPath, std::ios::binary);

			AssetType type = AssetType::Unknown;
			in.read(reinterpret_cast<char*>(&type), sizeof(int));

			return materialManager.Get(guid, in);
		}
	}
}