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

	void SpriteSheetAnimation::CreateDefualtJson(const std::string& aPath)
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();


		Document::AllocatorType& allocator = d.GetAllocator();


		Value framesList(kArrayType);
		{
			Math::Rect rect;
			Value frame = rect.Save(allocator);

			framesList.PushBack(frame, allocator);
		}

		Value animationsList(kArrayType);
		{
			Value animation(kObjectType);
			animation.AddMember("name", "AnimationName", allocator);

			Value list(kArrayType);
			list.PushBack(0, allocator);

			animation.AddMember("animations", list.Move(), allocator);

			animationsList.PushBack(animation, allocator);
		}

		d.AddMember("frames", framesList.Move(), allocator);
		d.AddMember("animations", animationsList.Move(), allocator);

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(aPath);
		ofs << buffer.GetString();
		ofs.close();
	}
}