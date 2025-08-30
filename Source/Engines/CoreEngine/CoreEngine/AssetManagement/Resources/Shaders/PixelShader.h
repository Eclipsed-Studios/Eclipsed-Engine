#pragma once

#include <AssetManagement/Resources/Abstract/AbstractResource.h>

namespace ENGINE_NAMESPACE
{
	class PixelShader : public AbstractResource
	{
		BASE_RESOURCE(PixelShader)

	public:
		const unsigned& GetPixelShaderID() const;

	protected:
		unsigned myPixelShaderID = 0;
	};
}