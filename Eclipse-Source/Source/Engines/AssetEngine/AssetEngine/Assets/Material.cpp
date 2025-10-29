#include "Material.h"
#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

#include "AssetEngine/Assets/Texture.h"

namespace Eclipse
{
	ASSET_OPERATORS_IMPL(Materials, Assets::MaterialHandle);

	void Materials::Use()
	{
		dataHandle->texture.Bind();

		//Math::Vector4f American_Colour = color.ToVector();
		//GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "material.color", &American_Colour);

		//myUniformManager.SetUniformVec4Float(material.color, shaderID, (Math::Vector4f*)aValue);
	}
}