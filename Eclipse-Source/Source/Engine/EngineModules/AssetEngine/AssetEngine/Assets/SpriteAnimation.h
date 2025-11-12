#pragma once

#include "Shader.h"

namespace Eclipse
{
	namespace Assets
	{
		struct ShaderHandle;
		class ShaderManager;
	}

	class VertexShaders final : public Shaders
	{
		using Shaders::Shaders;
		using Shaders::operator=;
	};
}