#include "PixelShaderAsset.h"

namespace Eclipse::Assets
{
	unsigned PixelShader::GetProgramID() const
	{
		return dataPtr->shaderProgramID;
	}

	void PixelShader::Bind()
	{
		glUseProgram(dataPtr->shaderProgramID);
	}
}