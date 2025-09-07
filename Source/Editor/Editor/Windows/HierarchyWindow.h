#pragma once

#include "Window.h"

namespace ENGINE_NAMESPACE::Editor
{
	class HierarchyWindow final : public AbstractWindow
	{
		BASE_WINDOW(HierarchyWindow, "Hierarchy")

	public:
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;
	};
}