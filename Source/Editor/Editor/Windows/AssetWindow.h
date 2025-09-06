#pragma once

#include "Window.h"

#include <filesystem>

namespace ENGINE_NAMESPACE::Editor
{
	class AssetWindow final : public AbstractWindow
	{
	public:
		AssetWindow(const int& aId = -1);

		void Open() override;
		void Update() override;
		void Close() override;

	public:
		float myButtonSizeMultiplier = 1.f;

		std::filesystem::path myCurrentPath;
		static inline std::filesystem::path Active_FilePath;
	};
}