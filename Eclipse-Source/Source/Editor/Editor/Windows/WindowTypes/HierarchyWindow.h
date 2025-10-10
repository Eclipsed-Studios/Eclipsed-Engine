#pragma once

#include "Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	class HierarchyWindow final : public AbstractWindow
	{
		BASE_SELECTION(HierarchyWindow, "Hierarchy")

	public:
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;
	};
}