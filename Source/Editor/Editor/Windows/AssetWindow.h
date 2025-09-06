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
		std::filesystem::path myCurrentPath;
	};
}