#pragma once

#include "WindowBase.h"

namespace ENGINE_NAMESPACE::Editor
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