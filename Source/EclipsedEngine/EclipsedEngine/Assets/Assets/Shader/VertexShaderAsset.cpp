#include "EclipsedEngine/Assets/Assets/Shader/VertexShaderAsset.h"

namespace Eclipse::Assets
{
	unsigned VertexShader::GetProgramID() const
	{
		return dataPtr->shaderProgramID;
	}
}