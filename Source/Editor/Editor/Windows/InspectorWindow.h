#pragma once

#include "Window.h"

#include "Components/Transform2D.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"

#include "ImGui/imgui.h"

namespace ENGINE_NAMESPACE::Editor
{
	class InspectorWindow final : public AbstractWindow
	{
	public:
		InspectorWindow(const int& aId = -1);

		void Open() override;
		void Update() override;
		void Close() override;

	private:
		template<typename T>
		void DrawInspector(T* aComp);

		void DrawComponentHeader(const char* compName, bool& isDrawn, const float values = 0, ImGuiStyleVar styleFlags = ImGuiStyleVar_FrameRounding);

	public:
		static inline unsigned CurrentGameObjectID;

		static inline constexpr int NAME_BUFFER_LENGTH = 256;
		char nameBuffer[NAME_BUFFER_LENGTH];
	};


	template<typename T>
	inline void InspectorWindow::DrawInspector(T* aComp)
	{
		if (Transform2D* comp = dynamic_cast<Transform2D*>(aComp))
		{
			DrawInspector(comp);
		}
		else if (SpriteRenderer2D* comp = dynamic_cast<SpriteRenderer2D*>(aComp))
		{
			DrawInspector(comp);
		}
		else if (SpriteSheetAnimator2D* comp = dynamic_cast<SpriteSheetAnimator2D*>(aComp))
		{
			DrawInspector(comp);
		}
	}

	template<>
	inline void InspectorWindow::DrawInspector(Transform2D* aComp)
	{
		DrawComponentHeader("Transform2D", aComp->myInspectorWasDrawn);
		if (!aComp->myInspectorWasDrawn) return;

		std::stringstream ss;
		ss << "##" << aComp;

		Math::Vector2f pos = aComp->GetPosition();
		Math::Vector2f scale = aComp->GetScale();
		float rot = aComp->GetRotation() * (180.f / 3.1415f);

		{ // Position
			ImGui::Text("Position");
			ImGui::SameLine();
			ImGui::DragFloat2(("##Position" + ss.str()).c_str(), &pos.x, 0.001f);
		}

		{ // Scale
			ImGui::Text("Scale");
			ImGui::SameLine();
			ImGui::DragFloat2(("##Scale" + ss.str()).c_str(), &scale.x, 0.1f);
		}

		{ // Rotation
			ImGui::Text("Rotation");
			ImGui::SameLine();
			ImGui::DragFloat(("##Rotation" + ss.str()).c_str(), &rot, 0.01f);
		}


		if (pos.x != aComp->GetPosition().x || pos.y != aComp->GetPosition().y)
		{
			aComp->SetPosition(pos);
		}

		if (scale.x != aComp->GetScale().x || scale.y != aComp->GetScale().y)
		{
			aComp->SetScale(scale);
		}

		if (rot != aComp->GetRotation())
		{
			aComp->SetRotation(rot * (3.1415f / 180.f));
		}
	}

	template<>
	inline void InspectorWindow::DrawInspector(SpriteRenderer2D* aComp)
	{
		DrawComponentHeader("SpriteRenderer2D", aComp->myInspectorWasDrawn);
		if (!aComp->myInspectorWasDrawn) return;

		ImGui::Text("SpriteRenderer2D");
	}

	template<>
	inline void InspectorWindow::DrawInspector(SpriteSheetAnimator2D* aComp)
	{
		DrawComponentHeader("SpriteSheetAnimator2D", aComp->myInspectorWasDrawn);
		if (!aComp->myInspectorWasDrawn) return;

		ImGui::Text("SpriteSheetAnimator2D");
	}
}