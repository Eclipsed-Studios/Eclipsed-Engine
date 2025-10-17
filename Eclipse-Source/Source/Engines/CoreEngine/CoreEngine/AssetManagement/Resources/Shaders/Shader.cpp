#include "Shader.h"

#include "OpenGL/glad/glad.h"
#include <AssetManagement/Resources.h>

namespace Eclipse
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

	void Shader::Use(unsigned aProgramID)
	{
		if (!aProgramID)
			aProgramID = myProgramID;
		
		glUseProgram(aProgramID);
	}
}