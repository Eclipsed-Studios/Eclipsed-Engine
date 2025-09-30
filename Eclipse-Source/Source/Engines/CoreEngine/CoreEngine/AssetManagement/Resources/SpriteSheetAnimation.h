#pragma once

#include "Abstract/AbstractResource.h"

#include "Math/Rect.h"

#include <vector>
#include <unordered_map>

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