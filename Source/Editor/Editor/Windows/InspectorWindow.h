#pragma once

#include "WindowBase.h"

namespace Eclipse::Editor
{
	class InspectorWindow final : public AbstractWindow
	{
		BASE_SELECTION(InspectorWindow, "Inspector");

	public:
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH] = {};
	};
}