#pragma once

#include "Asset.h"

namespace Eclipse
{
	namespace Assets
	{
		struct ShaderHandle;
		class ShaderManager;
	}

	class Shaders final
	{
		ASSET_OPERATORS_DEF(Shaders, Assets::ShaderHandle, Assets::ShaderManager);


	};
}