#pragma once

#include "WindowBase.h"

#include <filesystem>

#include "AssetManagement/Resources.h"
#include "Files/FileWatcher.h"
#include "Files/DirectoryTree.h"


namespace Eclipse::Editor
{
//	struct Directory {
//		std::vector<std::shared_ptr<Directory>> directories;
//		std::vector<Utilities::FileInfo*> files;
//		Utilities::FileInfo* currentPath;
//		std::shared_ptr<Directory> parent = nullptr;
//	};

	class AssetWindow final : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_2(AssetWindow, "Assets")

	public:
		void Open() override;
		void Update() override;

		void OpenFile(const Utilities::FileInfo& fifo);


	private:
		void HandleFileChanges(const FileWatcherEvent& event);

		void DrawAssetHiearchy(const char* path);

		void DrawContextMenu(const std::string& key, std::filesystem::path& aPath);

		bool CheckFileClicked();

	private:
		void DrawExplorerEntry(float windowWidth, const Utilities::FileInfo& file);
		void AssetEntry(float windowWidth, const Utilities::FileInfo& file);
		void DirectoryEntry(float windowWidth, Utilities::FileNode* directory);
		void DrawAssetExplorer(float width);


	public:
		static inline std::filesystem::path Active_FilePath;
		static inline std::filesystem::path Hiearchy_Active_FilePath;

		static inline float folderStructureWidth = 200.f;
		static inline float scrollBarWidth = 15.f;

		float myButtonSizeMultiplier = 1.f;

		std::string myPayloadStr;

		Utilities::DirectoryTree dirTree;
		Utilities::FileInfo* Active_Path = nullptr;
		Utilities::FileNode* activeDir = nullptr;
	};
}
