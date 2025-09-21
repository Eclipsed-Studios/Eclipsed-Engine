#pragma once

#include "WindowBase.h"

#include <filesystem>

#include "AssetManagement/Resources.h"


namespace Eclipse::Editor
{
	class AssetWindow final : public AbstractWindow
	{
		BASE_SELECTION(AssetWindow, "Assets")

	public:
		void Open() override;
		void Update() override;

		void OpenFile(const FileInfo& fifo);
		void OpenContextMenu(const FileInfo& fifo);

	public:
		float myButtonSizeMultiplier = 1.f;

		std::filesystem::path myCurrentPath;
		static inline std::filesystem::path Active_FilePath;

		std::string myPayloadStr;
	};
}
