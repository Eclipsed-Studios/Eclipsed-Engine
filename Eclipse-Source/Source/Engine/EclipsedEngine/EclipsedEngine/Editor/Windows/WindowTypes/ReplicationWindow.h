#pragma once

#include "EclipsedRuntime/Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	class ReplicationWindow final : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_3(ReplicationWindow, "Replication", "Settings");

	public:
		void Update() override;

	private:
		void DrawSceneEditor();
	};
}