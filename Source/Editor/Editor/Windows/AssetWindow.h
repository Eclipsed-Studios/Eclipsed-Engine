#pragma once

#include "Window.h"

#include <filesystem>

namespace ENGINE_NAMESPACE::Editor
{
	class AssetWindow final : public AbstractWindow
	{
		BASE_WINDOW(AssetWindow, "Assets")

	public:
		void Open() override;
		void Update() override;

	public:
		float myButtonSizeMultiplier = 1.f;

		std::filesystem::path myCurrentPath;
		static inline std::filesystem::path Active_FilePath;

		std::string myPayloadStr;
	};
}