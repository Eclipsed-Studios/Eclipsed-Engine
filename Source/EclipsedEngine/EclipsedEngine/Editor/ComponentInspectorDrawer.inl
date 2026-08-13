#ifdef ECL_EDITOR

#include "ComponentInspectorDrawer.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Editor
{
	template<typename T>
	inline void ComponentInspectorDrawer<T>::DrawInspector(T* comp)
	{
		ImGui::Text("Component not supported.");
	}
}

#endif