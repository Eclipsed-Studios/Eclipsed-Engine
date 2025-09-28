#include "SpriteSheetAnimation.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/prettywriter.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"



#include <fstream>

namespace Eclipse
{
	const Math::Rect& SpriteSheetAnimation::GetRect(unsigned aIdx) const
	{
		return myFrames[aIdx];
	}

	std::vector<unsigned> SpriteSheetAnimation::GetAnimation(const std::string& aName) const
	{
		if (myAnimations.find(aName) == myAnimations.end())
		{
			return {};
		}

		return myAnimations.at(aName);
	}
}