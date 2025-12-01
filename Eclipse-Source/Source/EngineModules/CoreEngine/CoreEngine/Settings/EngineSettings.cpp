#include "EngineSettings.h"

#include "CoreEngine/Macros/defines.h"


namespace Eclipse
{
	EngineSettings::EngineSettings() : Settings("settings.json")
	{
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
		doc[STRINGIFY(Engine_Name)].SetString(Engine_Name.c_str(), doc.GetAllocator());
		doc[STRINGIFY(Engine_Version)].SetString(Engine_Version.c_str(), doc.GetAllocator());

		{
			rapidjson::Value resolution(rapidjson::kObjectType);
			resolution.AddMember("x", Resolution.x, doc.GetAllocator());
			resolution.AddMember("y", Resolution.y, doc.GetAllocator());

			doc.AddMember(STRINGIFY(Resolution), resolution.Move(), doc.GetAllocator());
		}
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
}