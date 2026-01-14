#include "Shader.h"

#include <glad/glad.h>
#include "AssetEngine/Models/AssetDatas/Handles/ShaderHandle.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Shaders, Assets::ShaderHandle);

	unsigned Shaders::GetProgramID() const
	{
		return dataHandle->shaderID;
	}

	void Shaders::Bind()
	{
		glUseProgram(dataHandle->shaderID);
	}

}