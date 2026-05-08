#include "VertexShaderAsset.h"

namespace Eclipse::Assets
{
	unsigned VertexShader::GetProgramID() const
	{
		return dataPtr->shaderProgramID;
	}

	void VertexShader::Bind()
	{
		glUseProgram(dataPtr->shaderProgramID);
	}
}