#ifdef ECLIPSED_EDITOR

#include "ComponentInspectorDrawer.h"

#include "ImGui/imgui.h"

/*
* USE THIS FILE TO CREATE CUSTOM INSPECTORS FOR GAME COMPONENTS.
*/

namespace Eclipse::Editor
{
	class Simon;
	void DrawInspector(Simon* comp)
	{
		ImGui::Text("This is the way.");
	}

	REGISTER_INSPECTOR(Simon);


	class Player;
	void DrawInspector(Player* comp)
	{
		ImGui::Text("This is the other way.");
	}

	REGISTER_INSPECTOR(Player);
}

#endif