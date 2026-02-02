#pragma once

#include "AssetEngine/Runtime/Managers/AssetManager.h"
#include "AssetEngine/SupportedTypes.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace Eclipse
{
	class Resources	{
	public:
		template<typename T>
		static T Get(const std::string& aGuid);

	private:
		static VertexShaderManager vertexShaderManager;
		static PixelShaderManager pixelShaderManager;
		static MaterialManager materialManager;
		static TextureManager textureManager;
	};

	template<typename T>
	inline T Resources::Get(const std::string& aGuid)
	{
		if (aGuid.empty()) return {};

		const std::filesystem::path ad = "F:/Projects/Eclipsed-Engine/RPS-Project/Project";
		std::filesystem::path exportFolderPath = ad / "Artifacts" / aGuid.substr(0, 2) / aGuid;

		std::ifstream in(exportFolderPath, std::ios::binary);

		AssetType type = AssetType::Unknown;
		in.read(reinterpret_cast<char*>(&type), sizeof(int));

		if constexpr (std::is_same<T, Texture>::value) return textureManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, VertexShader>::value) return vertexShaderManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, PixelShader>::value) return pixelShaderManager.Get(aGuid, in);
		else if constexpr (std::is_same<T, Material>::value) return materialManager.Get(aGuid, in);
	}
}