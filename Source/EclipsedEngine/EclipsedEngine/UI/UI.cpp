#include "UI.h"

#include "ImGui/ImGui.h"

namespace Eclipse
{
	void UI::Begin(const char* name, bool* isOpen, UIWindowFlags flags)
	{
		ImGui::Begin(name, isOpen, flags);
	}

	void UI::End()
	{
		ImGui::End();
	}

	void UI::Text(const char* text)
	{
		ImGui::Text(text);
	}
}
