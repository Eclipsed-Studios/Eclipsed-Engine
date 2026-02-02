#pragma once

#include "AssetEngine/Editor/Importer/IEditorAssetImporter.h"

namespace Eclipse
{
	class TextureImporter : public IEditorAssetImporter
	{
	public:
		void Export(const AssetMetaSettings& metaSettings, std::ofstream& outStream, const std::filesystem::path& aPath) override;
	};
}