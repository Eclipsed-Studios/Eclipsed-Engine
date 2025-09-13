#pragma once

#include <AssetManagement/Resources/Abstract/AbstractResource.h>

namespace Eclipse
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