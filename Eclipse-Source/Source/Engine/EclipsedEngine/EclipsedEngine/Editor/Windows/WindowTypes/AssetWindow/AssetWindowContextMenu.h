#pragma once

#include "EclipsedEngine/Editor/Windows/AbstractContextMenu.h"

namespace Eclipse::Editor 
{
	class AssetWindowContextMenu  : public AbstractContextMenu {
	public:
		AssetWindowContextMenu();

		void SetActivePath(const std::filesystem::path& aPath);
		void Update() override;

	private:
		void CreateMenu();
		std::filesystem::path activePath;
	};
}