#pragma once

#include "Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	class HierarchyWindow final : public AbstractWindow
	{
		BASE_SELECTION(HierarchyWindow, "Hierarchy")

	public:
		void HierarchyButton(GameObject* aGameObject, GameObjectID aGOID);
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;
	};
}