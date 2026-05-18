#ifdef ECLIPSED_EDITOR
#include "ProfilerWindow.h"

#include <ImGui/imgui.h>
#include "EclipsedEngine/Profiler.h"

namespace Eclipse::Editor
{
	void ProfilerWindow::Update()
	{
		if (ImGui::Button("PRAOKPAWD"))
		{
			Profiler::CollectNextFrame();
		}
	}
}

#endif