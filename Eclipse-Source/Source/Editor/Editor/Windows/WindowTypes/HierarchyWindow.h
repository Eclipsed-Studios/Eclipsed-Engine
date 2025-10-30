#pragma once

#include "Editor/Windows/WindowBase.h"

namespace Eclipse
{
	class GameObject;
	namespace Editor
	{
		class HierarchyWindow final : public AbstractWindow
		{
			BASE_SELECTION(HierarchyWindow, "Hierarchy")

		public:
            void HierarchyButton(GameObject* aGameObject, float totalIndent);
            void AssignParentChildren(GameObject* targetGO, Eclipse::GameObject* aGameObject);
			void Update() override;

		public:
			static inline unsigned CurrentGameObjectID;
		};
	}
}