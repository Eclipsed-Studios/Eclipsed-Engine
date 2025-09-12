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
		const Math::Rect& GetRect(unsigned aIdx) const;
		std::vector<unsigned> GetAnimation(const std::string& aName) const;

		static void CreateDefualtJson(const std::string& aPath);

	private:
		std::vector<Math::Rect> myFrames;
		std::unordered_map<std::string, std::vector<unsigned>> myAnimations;
	};
}