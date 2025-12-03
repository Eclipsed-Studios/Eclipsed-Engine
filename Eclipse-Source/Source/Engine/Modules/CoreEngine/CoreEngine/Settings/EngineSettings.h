#pragma once

#include "Settings.h"

namespace Eclipse
{
	class EngineSettings : public Settings
	{
	public:
		EngineSettings();
		~EngineSettings();

	public:
		const std::string& GetEngineName();
		const std::string& GetEngineVersion();

	public:
		const Math::Vector2i& GetResolution() const;
		void SetResolution(const Math::Vector2i& res);

		const Math::Vector2f& GetOneDivResolution() const;
		float GetResolutionRation() const;


	private:
		std::string Engine_Name = "Eclipsed";
		std::string Engine_Version = "0.0.0";

		Math::Vector2i Resolution = { 1280, 720 };
		Math::Vector2f myOneDivResolution = { 0.f, 0.f };
		float myResolutionRatio = 0.f;
	};
}