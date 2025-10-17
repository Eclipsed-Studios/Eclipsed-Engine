#ifdef ECLIPSED_EDITOR
#pragma once

#include "Editor/Windows/WindowBase.h"

#include "Files/DirectoryTree.h"
#include "Editor/Windows/WindowTypes/AssetWindow/AssetWindowContextMenu.h"

namespace Eclipse::Editor
{
	class AssetWindow final : public AbstractWindow
	{
		BASE_SELECTION(AssetWindow, "Assets")

	public:
		void Open();

		void Update();

	private:

		void DrawAssetView();
		void DrawAssetHierachy();
		void DrawAssetHierachyEntry(Utilities::FileNode* node);


		void OpenFile(const Utilities::FileInfo& fifo);

	private:
		bool CheckFileDoubleClicked();
		bool CheckFileClicked();

		void DrawAssetViewBreadcrumb();

		void DrawAssetViewEntry(const Utilities::FileNode* parent);
		void CheckAssetViewEntryClicked(const Utilities::FileNode* parent);

	private:
		static inline float folderStructureWidth = 215.f;
		static inline float scrollBarWidth = 15.f;

		float myButtonSizeMultiplier = 1.f;
		unsigned entryIndex = 0;
		static inline int ActiveEntryIndex = -1;

	private:
		Utilities::DirectoryTree dirTree;

		Utilities::FileNode* Active_View_Node;
		Utilities::FileNode* Active_Hierarchy_Node;

		AssetWindowContextMenu ctxMenu{};

	public:
		static inline std::filesystem::path ActivePath;
	};
}
#endif