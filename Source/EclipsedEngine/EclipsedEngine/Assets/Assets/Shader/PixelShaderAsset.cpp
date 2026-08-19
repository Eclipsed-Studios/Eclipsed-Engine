#include "EclipsedEngine/Assets/Assets/Shader/PixelShaderAsset.h"

namespace Eclipse::Assets
{
	unsigned PixelShader::GetProgramID() const
	{
		return dataPtr->shaderProgramID;
	}
}