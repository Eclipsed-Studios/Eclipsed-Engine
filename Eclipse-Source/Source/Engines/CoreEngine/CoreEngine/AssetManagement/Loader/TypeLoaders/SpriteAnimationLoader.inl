#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/SpriteSheetAnimation.h>

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/writer.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

#include <fstream>

namespace Eclipse
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, SpriteSheetAnimation& outResource)
	{
		using namespace rapidjson;
		std::filesystem::path resolvedPath = aPath;
		if (resolvedPath.is_relative())
		{
			resolvedPath = std::filesystem::current_path().parent_path().generic_string() + "/" + resolvedPath.string();
		}
		else if (resolvedPath.is_absolute())
		{
			resolvedPath = aPath;
		}

		std::ifstream ifs(resolvedPath.string().c_str());
		if (!ifs.is_open())
		{
			throw std::runtime_error("No file.");
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		if (d.Parse(jsonString.c_str()).HasParseError())
		{
			throw std::runtime_error("The json had parsing errors.");
		}

		if (d.HasMember("frames"))
		{
			const Value& frames = d["frames"];
			for (const Value& frame : frames.GetArray())
			{
				Math::Rect animationFrame;
				animationFrame.Load(frame);

				outResource.myFrames.push_back(animationFrame);
			}
		}


		if (d.HasMember("animations"))
		{
			const Value& animations = d["animations"];
			for (const Value& animation : animations.GetArray())
			{
				const Value& nameVal = animation["name"];
				std::string name = nameVal.GetString();

				std::vector<unsigned>& animations = outResource.myAnimations[name];

				const Value& animationsList = animation["animations"];
				for (const Value& animVal : animationsList.GetArray())
				{
					animations.push_back(animVal.GetUint());
				}
			}
		}
	}
}