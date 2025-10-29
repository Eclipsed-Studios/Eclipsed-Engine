#pragma once

#include "Asset.h"

namespace Eclipse
{
	namespace Assets
	{
		struct MaterialHandle;
		class MaterialManager;
	}

	class Materials final
	{
		ASSET_OPERATORS_DEF(Materials, Assets::MaterialHandle, Assets::MaterialManager);

	public:
		void Use();
	};
}