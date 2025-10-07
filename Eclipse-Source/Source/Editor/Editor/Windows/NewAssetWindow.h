#ifdef _EDITOR
#pragma once

#include "WindowBase.h"

#include "Files/DirectoryTree.h"

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



	private:
		bool CheckFileClicked();

		void D();

		void DrawAssetViewEntry(const Utilities::FileNode* parent);
		void CheckAssetViewEntryClicked(const Utilities::FileNode* parent);

	private:
		static inline float folderStructureWidth = 200.f;
		static inline float scrollBarWidth = 15.f;

		float myButtonSizeMultiplier = 1.f;

	private:
		Utilities::DirectoryTree dirTree;

		Utilities::FileNode* ActiveNode;
		std::filesystem::path ActivePath;
	};
}
#endif