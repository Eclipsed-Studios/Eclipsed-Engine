#include "AbstractContextMenu.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	AbstractContextMenu::AbstractContextMenu(const char* name) : ctxName(name)
	{

	}

	void AbstractContextMenu::Draw()
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup(ctxName);
		}

		UpdateAlways();

		if (BeginMenu())
		{
			Update();
			EndMenu();
		}
	}

	bool  AbstractContextMenu::BeginMenu() const
	{
		if (ImGui::BeginPopup(ctxName))
		{
			/*ImGui::FocusPreviousWindowIgnoringOne(ImGui::GetCurrentWindow());*/
			return true;
		}
		return false;
	}

	void AbstractContextMenu::EndMenu() const
	{
		ImGui::EndPopup();
	}
}
