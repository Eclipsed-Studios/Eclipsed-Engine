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


	private:
		void DrawAssetHiearchy(const char* path);
		void DrawAssetExplorer(float width);

		void DrawContextMenu(const std::string& key, std::filesystem::path& aPath);

		void CheckFileClicked(const std::filesystem::path& aPath);

		std::vector<std::filesystem::directory_entry> GetDirectoryEntries(const std::filesystem::path& aPath, bool sort = false);

	public:
		static inline float folderStructureWidth = 200.f;
		static inline float scrollBarWidth = 15.f;

		float myButtonSizeMultiplier = 1.f;

		bool myDirectoryHiearchyShowFiles = true;

		std::filesystem::path myCurrentPath;
		static inline std::filesystem::path Active_FilePath;
		static inline std::filesystem::path Hiearchy_Active_FilePath;

		std::string myPayloadStr;
	};
}
