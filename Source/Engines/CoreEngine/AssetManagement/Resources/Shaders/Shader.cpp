#include "Shader.h"

#include "glad/glad.h"
#include <AssetManagement/Resources.h>

namespace ENGINE_NAMESPACE
{
	void Shader::Create(const char* aPixelShaderPath, const char* aVertexShaderPath)
	{
		myPixelShader = Resources::Get<PixelShader>(aPixelShaderPath);
		myVertexShader = Resources::Get<VertexShader>(aVertexShaderPath);

		myProgramID = glCreateProgram();
		glAttachShader(myProgramID, myVertexShader->GetVertexShaderID());
		glAttachShader(myProgramID, myPixelShader->GetPixelShaderID());
		glLinkProgram(myProgramID);
	}

	void Shader::Use()
	{
		glUseProgram(myProgramID);
	}
}