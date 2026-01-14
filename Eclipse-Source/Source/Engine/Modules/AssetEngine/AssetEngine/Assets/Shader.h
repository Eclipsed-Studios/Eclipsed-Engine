#pragma once

#include "Asset.h"

namespace Eclipse
{
	namespace Assets
	{
		struct ShaderHandle;
		class ShaderManager;
	}

	class Shaders 
	{
		ASSET_OPERATORS_DEF(Shaders, Assets::ShaderHandle, Assets::ShaderManager);

	public:
		unsigned GetProgramID() const;

		void Bind();

	};
}