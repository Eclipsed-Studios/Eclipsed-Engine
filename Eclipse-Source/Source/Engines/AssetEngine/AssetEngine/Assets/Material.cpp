#include "Material.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

#include "AssetEngine/Assets/Texture.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Materials, Assets::MaterialHandle);

	void Materials::Use()
	{
		dataHandle->texture.Bind();

		Math::Vector4f col = dataHandle->color.ToVector();
		GraphicsEngine::SetUniform(UniformType::Vector4f, dataHandle->programID, "material.color", &col);
	}

	void Materials::Create()
	{
		dataHandle->programID = glCreateProgram();
		glAttachShader(dataHandle->programID, dataHandle->vs.GetProgramID());
		glAttachShader(dataHandle->programID, dataHandle->ps.GetProgramID());
		glLinkProgram(dataHandle->programID);
	}
}