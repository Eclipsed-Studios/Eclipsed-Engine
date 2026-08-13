#pragma once

#include "EclipsedEngine/Editor/Windows/WindowBase.h"


#include "Core/Math/Vector/Vector2.h"

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