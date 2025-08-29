#pragma once

#include "Abstract/AbstractResource.h"

namespace ENGINE_NAMESPACE
{
	class Texture : public AbstractResource
	{
		BASE_RESOURCE(Texture)

	private:
		unsigned textureID = 0;
	};
}