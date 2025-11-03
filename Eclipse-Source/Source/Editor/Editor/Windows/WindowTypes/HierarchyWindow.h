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
			void AssignParentChildren(GameObject* targetGO, Eclipse::GameObject* aGameObject);
			void Update() override;

		public:
			static inline unsigned CurrentGameObjectID;

			static void Copy();
			static void Paste();
		private:
			
			static void CopyGameObject(unsigned activeGO, rapidjson::Value& gameobjectJson, rapidjson::Document::AllocatorType& anAllocator);
			static void PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator);

			void CopyPasteManager();

			void RecursiveDeleteChildren(GameObject*& aGameObject);

			std::set<unsigned> gameobjectIdsThatAreOpen;
		};
	}
}