#ifdef _EDITOR
#pragma once

#include "WindowBase.h"

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

	private:
		void DrawGameObjectInspector();
		void DrawAssetInspector();

		template<typename T>
		void DrawComponentInspector() {}

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH] = {};
		static inline ActiveItemTypes_ activeType;
	};
}
#endif