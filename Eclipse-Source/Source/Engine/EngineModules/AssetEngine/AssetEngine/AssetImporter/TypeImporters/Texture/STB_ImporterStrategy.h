#pragma once

#include "AssetEngine/AssetImporter/TypeImporters/AssetImporterStrategy.h"
#include "AssetEngine/Models/AssetDatas/Binary/TextureBinaryData.h"

namespace Eclipse::Assets
{
	class STB_ImporterStrategy : public AssetImporterStrategy<TextureBinaryData>
	{
	public:
		void ImportAsset(TextureBinaryData& outData, const char* path) override;
	};
}