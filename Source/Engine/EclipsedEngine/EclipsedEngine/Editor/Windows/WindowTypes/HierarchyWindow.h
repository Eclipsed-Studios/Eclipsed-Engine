#ifdef ECLIPSED_EDITOR
#pragma once

#include "EclipsedEngine/Editor/Windows/WindowBase.h"

#include <vector>
#include <set>
#include <filesystem>

#include <rapidjson/document.h>


namespace Eclipse
{
	class Canvas;
	class GameObject;

	namespace Editor
	{
		class HierarchyWindow final : public AbstractWindow
		{
			EDITOR_WINDOW_BASE_2(HierarchyWindow, "Hierarchy")

		public:
			static void OpenParents(unsigned aParentID);
			void HierarchyButton(GameObject* aGameObject, float totalIndent);
			void AssignParentChildren(GameObject* targetGO, GameObject* aGameObject);
			void Update() override;

			static void CreatePrefab(unsigned aGameobjectID, std::filesystem::path aPath);

		public:
			static inline unsigned CurrentGameObjectID;

			Canvas* GetParentCanvas(GameObject* BaseObject);

			bool CheckCopomentType(GameObject* aGameobject, GameObject* aParent);

			static inline std::set<unsigned> gameobjectIdsThatAreOpen;

			unsigned SelectedGameobjectID;
			
			bool gameobjectrightclicked;
		};
	}
}
#endif