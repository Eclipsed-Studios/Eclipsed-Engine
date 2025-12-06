#include "pch.h"

#include "EngineSettings.h"

#include "CoreEngine/Macros/defines.h"


namespace Eclipse
{
	EngineSettings::EngineSettings() : Settings("settings.json")
	{
		if (!fileOpenend) return;

		Engine_Name = doc[STRINGIFY(Engine_Name)].GetString();
		Engine_Version = doc[STRINGIFY(Engine_Version)].GetString();

		{
			rapidjson::Value& resVal = doc[STRINGIFY(Resolution)];

			Math::Vector2i resolution;
			resolution.x = resVal["x"].GetInt();
			resolution.y = resVal["y"].GetInt();

			SetResolution(resolution);
		}
	}

	EngineSettings::~EngineSettings()
	{
		//doc.AddMember(STRINGIFY(Engine_Name), rapidjson::Value(Engine_Name.c_str(), doc.GetAllocator()).Move(), doc.GetAllocator());
		//doc.AddMember(STRINGIFY(Engine_Version), rapidjson::Value(Engine_Version.c_str(), doc.GetAllocator()).Move(), doc.GetAllocator());
		//	
		//{
		//	rapidjson::Value resolution(rapidjson::kObjectType);
		//	resolution.AddMember("x", Resolution.x, doc.GetAllocator());
		//	resolution.AddMember("y", Resolution.y, doc.GetAllocator());

		//	doc.AddMember(STRINGIFY(Resolution), resolution.Move(), doc.GetAllocator());
		//}
	}

	const std::string& EngineSettings::GetEngineName()
	{
		return Engine_Name;
	}

	const std::string& EngineSettings::GetEngineVersion()
	{
		return Engine_Version;
	}

	const Math::Vector2i& EngineSettings::GetResolution() const
	{
		return Resolution;
	}

	void EngineSettings::SetResolution(const Math::Vector2i& res)
	{
		Resolution = res;

		if(Resolution.x == 0.f || Resolution.y)
		{
			myOneDivResolution = { 0.f, 0.f };
			myResolutionRatio = 0.f;
			return;
		}

		myOneDivResolution = { 1.f / Resolution.x, 1.f / Resolution.y };
		myResolutionRatio = Resolution.y / Resolution.x;
	}

	const Math::Vector2f& EngineSettings::GetOneDivResolution() const
	{
		return myOneDivResolution;
	}

	float EngineSettings::GetResolutionRation() const
	{
		return myResolutionRatio;
	}
	
	const Math::Vector2i& EngineSettings::GetGameResolution() const
	{
		return myGameWindowResolution;
	}

	Math::Vector2i& EngineSettings::GetGameResolution()
	{
		return myGameWindowResolution;
	}
	
	void EngineSettings::SetGameResolution(const Math::Vector2i& res)
	{
		myGameWindowResolution = res;
		if (myGameWindowResolution.x == 0.f || myGameWindowResolution.y)
		{
			myResolutionRatioGameView = 0.f;
			return;
		}

		myResolutionRatioGameView = Resolution.y / Resolution.x;
	}

	float EngineSettings::GetGameResolutionRation() const
	{
		return myResolutionRatio;
	}
	float& EngineSettings::GetGameResolutionRation()
	{
		return myResolutionRatio;
	}
}