#include "TextureBinaryData.h"

#include "AssetEngine/AssetImporter/Helpers/STB_Helper.h"

Eclipse::Assets::TextureBinaryData::~TextureBinaryData()
{
	if (!pixels) return;

	STB_Helper::FreeData_STB(pixels);
}
