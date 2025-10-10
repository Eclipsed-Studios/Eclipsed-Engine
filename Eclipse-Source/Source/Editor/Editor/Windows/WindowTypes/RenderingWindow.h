#pragma once

#include "Editor/Windows/WindowBase.h"


#include "Math/Vector/Vector2.h"

namespace Eclipse::Editor
{
	class BaseRenderingWindow 
	{
	protected:
		void DrawGizmoPopup();
		void DrawGizmoButtons(bool& drawGizmo);

	public:
		static inline bool DrawGizmo = false;
	};
}