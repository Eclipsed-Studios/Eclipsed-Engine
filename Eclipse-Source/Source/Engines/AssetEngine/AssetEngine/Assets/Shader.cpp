#include "Shader.h"

#include <glad/glad.h>
#include "AssetEngine/Models/AssetDatas/Handles/ShaderHandle.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Shaders, Assets::ShaderHandle);

	size_t Shaders::GetAssetID() const
	{
		return dataHandle->assetID;
	}

	unsigned Shaders::GetProgramID() const
	{
		return dataHandle->shaderID;
	}

	void Shaders::Bind(int slot)
	{
		glUseProgram(dataHandle->shaderID);
	}

}