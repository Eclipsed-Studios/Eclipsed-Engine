#pragma once

#include <AssetManagement/Resources/Abstract/AbstractResource.h>

namespace ENGINE_NAMESPACE
{
	class VertexShader : public AbstractResource
	{
		BASE_RESOURCE(VertexShader)

	public:
		const unsigned& GetVertexShaderID() const;

	protected:
		unsigned myVertexShaderID = 0;
	};
}