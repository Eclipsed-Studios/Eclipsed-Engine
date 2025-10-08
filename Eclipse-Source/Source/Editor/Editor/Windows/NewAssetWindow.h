#ifdef _EDITOR
#pragma once

#include "WindowBase.h"

#include "Files/DirectoryTree.h"
#include "Editor/ContextMenus/AssetWindowContextMenu.h"

namespace Eclipse::Editor
{
	class NewAssetWindow final : public AbstractWindow
	{
		BASE_SELECTION(NewAssetWindow, "New Asset Window")

	public:
		void Open();

		void Update();

	private:
		
		void DrawAssetView();

		void OpenFile(const Utilities::FileInfo& fifo);

	private:
		bool CheckFileDoubleClicked();
		bool CheckFileClicked();

		void DrawAssetViewBreadcrumb();

		void DrawAssetViewEntry(const Utilities::FileNode* parent);
		void CheckAssetViewEntryClicked(const Utilities::FileNode* parent);

	private:
		static inline float folderStructureWidth = 200.f;
		static inline float scrollBarWidth = 15.f;

		float myButtonSizeMultiplier = 1.f;
		unsigned entryIndex = 0;
		static inline int ActiveEntryIndex = -1;

	private:
		Utilities::DirectoryTree dirTree;

		Utilities::FileNode* ActiveNode;
		static inline std::filesystem::path ActivePath;

		AssetWindowContextMenu ctxMenu{};
	};
}
#endif