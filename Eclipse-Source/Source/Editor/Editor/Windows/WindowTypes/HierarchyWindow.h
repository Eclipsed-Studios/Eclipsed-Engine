#pragma once

#include "Editor/Windows/WindowBase.h"

#include <vector>

#include <rapidjson/rapidjson/document.h>

#include <set>

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
			void AssignParentChildren(GameObject* targetGO, GameObject* aGameObject);
			void Update() override;

		public:
			static inline unsigned CurrentGameObjectID;

			void RecursiveDeleteChildren(GameObject*& aGameObject);

			bool CheckCopomentType(GameObject* aGameobject, GameObject* aParent);

			std::set<unsigned> gameobjectIdsThatAreOpen;
		};
	}
}