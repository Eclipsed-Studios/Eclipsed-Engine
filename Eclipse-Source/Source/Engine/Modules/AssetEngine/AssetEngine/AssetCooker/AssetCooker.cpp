#include "AssetCooker.h"

namespace Eclipse::Assets
{
	CookedAsset AssetCooker::Cook(const ImportedAsset& imported)
	{
		CookedAsset cooked;
		switch (imported.type)
		{
		case AssetType::Texture: textureCooker.Cook(std::get<TextureBinaryData>(imported.data), cooked);
		}

		return cooked;
	}
}