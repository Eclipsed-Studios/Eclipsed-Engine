#pragma once

#include <CoreEngine/AssetManagement/Resources/Abstract/AbstractResource.h>

namespace Eclipse
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