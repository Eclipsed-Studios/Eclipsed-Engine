#ifdef ECLIPSED_EDITOR

#include "ComponentInspectorDrawer.h"
#include "CoreEngine/Macros/defines.h"

namespace Eclipse::Editor
{
	template<typename T>
	inline void ComponentInspectorDrawer<T>::DrawInspector(T* comp)
	{
		ImGui::Text("Component not supported.");
	}
}

#endif