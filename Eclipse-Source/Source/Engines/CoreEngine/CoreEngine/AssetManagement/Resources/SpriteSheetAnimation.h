#pragma once

#include <vector>
#include <unordered_map>

#include "Utilities/Math/Rect.h"
#include "Abstract/AbstractResource.h"

namespace Eclipse
{

	class SpriteSheetAnimation : public AbstractResource
	{
		BASE_RESOURCE(SpriteSheetAnimation)

	public:
		const std::vector<unsigned>& GetAnimation(const std::string& aName) const;

	private:
		std::unordered_map<std::string, std::vector<unsigned>> myAnimations;
		std::vector<unsigned> emptyFrames;
	};
}