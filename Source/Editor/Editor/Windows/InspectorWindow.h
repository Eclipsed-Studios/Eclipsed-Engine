#pragma once

#include "WindowBase.h"

namespace ENGINE_NAMESPACE::Editor
{
	class InspectorWindow final : public AbstractWindow
	{
		BASE_SELECTION(InspectorWindow, "Inspector", "GRiann/SimonIsShit");

	public:
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH] = {};
	};
}