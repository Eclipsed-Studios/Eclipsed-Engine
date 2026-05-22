#pragma once

#ifdef ECLIPSED_EDITOR

#include "CoreEngine/Macros/defines.h"
#include <unordered_map>
#include <string>

namespace Eclipse::Editor
{
	using InspectorDrawFn = void(*)(void*);

	class ECLIPSED_API ComponentInspectorRegistry
	{
	public:
		static void Register(std::string name, InspectorDrawFn fn);
		static InspectorDrawFn GetDrawFunction(std::string name);

	private:
		static std::unordered_map<std::string, InspectorDrawFn> registry;
	};


	template<typename T>
	class ECLIPSED_API ComponentInspectorDrawer
	{
	public:
		static void DrawInspector(T* comp);
	};
}

#endif