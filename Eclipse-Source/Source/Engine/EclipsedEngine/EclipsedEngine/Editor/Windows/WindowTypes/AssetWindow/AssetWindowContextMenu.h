#pragma once

#include "EclipsedEngine/Editor/Windows/AbstractContextMenu.h"

namespace Eclipse::Editor 
{
	class AssetWindowContextMenu  : public AbstractContextMenu {
	public:
		AssetWindowContextMenu();

		void SetActivePath(const std::filesystem::path& aPath);
		void Update() override;
		void UpdateAlways() override;

	private:
		void CreateMenu();
		std::filesystem::path activePath;


		std::filesystem::path activePathAtRenaming;
		bool Renaming = false;
		char tempName[512];
	};
}