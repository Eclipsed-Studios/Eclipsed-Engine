#ifdef ECLIPSED_EDITOR
#pragma once

#include "Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	enum ActiveItemTypes_
	{
		ActiveItemTypes_None,
		ActiveItemTypes_GameObject,
		ActiveItemTypes_Asset
	};

	class InspectorWindow final : public AbstractWindow
	{
		BASE_SELECTION(InspectorWindow, "Inspector");

	public:
		void Update() override;

		static void SetActiveType(ActiveItemTypes_ aType)
		{
			if (lockInspector)
				return;

			activeType = aType;
		}

	private:
		void DrawGameObjectInspector();
		void DrawAssetInspector();

		void DrawTextureAssetInspector();
		void DrawMaterialAssetInspector();



		template<typename T>
		void DrawComponentInspector() {}

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH] = {};

	private:
		static inline bool lockInspector = false;
		static inline ActiveItemTypes_ activeType;
	};
}
#endif