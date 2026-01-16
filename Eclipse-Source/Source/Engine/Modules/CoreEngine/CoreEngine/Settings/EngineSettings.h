#pragma once

#include "Settings.h"
#include "CoreEngine/Math/Vector/Vector2.h"
#include <string>

namespace Eclipse
{
	class EngineSettings : public HejsanKOmis
	{
	//public:
		EngineSettings() = default;
		~EngineSettings() = default;

	//public:
	//	const std::string& GetEngineName();
	//	const std::string& GetEngineVersion();

	//public:
	//	const Math::Vector2i& GetResolution() const;
	//	void SetResolution(const Math::Vector2i& res);

	//	const Math::Vector2f& GetOneDivResolution() const;
	//	float GetResolutionRation() const;

	//	const Math::Vector2i& GetGameResolution() const;
	//	Math::Vector2i& GetGameResolution();
	//	void SetGameResolution(const Math::Vector2i& res);

	//	float GetGameResolutionRation() const;
	//	float& GetGameResolutionRation() ;

	//private:
	//	Math::Vector2i Resolution = { 1280, 720 };
	//	Math::Vector2f myOneDivResolution = { 0.f, 0.f };
	//	float myResolutionRatio = 0.f;

	//	float myResolutionRatioGameView = 0.f;
	//	Math::Vector2i myGameWindowResolution = { 1920, 1080 };
	};
}