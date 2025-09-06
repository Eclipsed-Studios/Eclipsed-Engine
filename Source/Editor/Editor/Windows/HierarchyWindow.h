#pragma once

#include "Window.h"

namespace ENGINE_NAMESPACE::Editor
{
	class HierarchyWindow final : public AbstractWindow
	{
	public:
		HierarchyWindow(const int& aId = -1);

		void Open() override;
		void Update() override;
		void Close() override;

	public:
		static inline unsigned CurrentGameObjectID;
	};
}