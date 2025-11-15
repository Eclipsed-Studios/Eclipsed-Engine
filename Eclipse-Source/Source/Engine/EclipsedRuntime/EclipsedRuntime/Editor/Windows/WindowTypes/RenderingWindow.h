#pragma once

#include "EclipsedRuntime/Editor/Windows/WindowBase.h"


#include "Utilities/Math/Vector/Vector2.h"

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