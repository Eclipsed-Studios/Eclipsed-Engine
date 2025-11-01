#pragma once

#include "Editor/Windows/WindowBase.h"

#include <vector>

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

			static void Copy();
			static void Paste();
		private:

			void CopyPasteManager();			
		};
	}
}