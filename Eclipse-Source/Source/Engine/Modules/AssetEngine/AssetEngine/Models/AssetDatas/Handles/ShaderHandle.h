#pragma once

#include "AssetHandle.h"

namespace Eclipse::Assets 
{
	struct ShaderHandle : public AssetHandle
	{
		unsigned shaderID;
	};
};