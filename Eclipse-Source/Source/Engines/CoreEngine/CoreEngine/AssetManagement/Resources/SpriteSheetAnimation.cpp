#include "SpriteSheetAnimation.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/prettywriter.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"



#include <fstream>

namespace Eclipse
{
	const std::vector<unsigned>& SpriteSheetAnimation::GetAnimation(const std::string& aName) const
	{
		if (myAnimations.find(aName) == myAnimations.end())
			return emptyFrames;

		return myAnimations.at(aName);
	}
}