#pragma once

#include "Window.h"

#include "Components/Transform2D.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/AudioSource.h"

#include "ImGui/imgui.h"

namespace ENGINE_NAMESPACE::Editor
{
	class InspectorWindow final : public AbstractWindow
	{
		BASE_WINDOW(InspectorWindow, "Inspector");

	public:
		void Update() override;

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH] = {};
	};
}