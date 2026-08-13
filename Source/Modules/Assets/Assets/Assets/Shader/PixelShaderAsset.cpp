#include "Assets/Assets/Shader/PixelShaderAsset.h"

#include "OpenGL/glad/glad.h"

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