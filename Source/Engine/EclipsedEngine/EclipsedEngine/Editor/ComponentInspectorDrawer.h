#pragma once

#ifdef ECLIPSED_EDITOR

#include "CoreEngine/Macros/defines.h"
#include <unordered_map>
#include <string>



#define REGISTER_INSPECTOR(cls)																						\
		struct cls##_inspector_registrar																			\
		{																											\
			cls##_inspector_registrar() 																			\
			{																										\
				Eclipse::Editor::ComponentInspectorRegistry::Register(												\
					#cls,																							\
					[](void* ptr)																					\
					{																								\
						DrawInspector(reinterpret_cast<cls*>(ptr));					\
					}																								\
				);																									\
			}																										\
		};																											\
		static cls##_inspector_registrar cls##_inspector_registrar_instance;


namespace Eclipse::Editor
{
	using InspectorDrawFn = void(*)(void*);

	class ECLIPSED_API ComponentInspectorRegistry
	{
	public:
		static std::unordered_map<std::string, InspectorDrawFn>& Registry();

		static void Register(std::string name, InspectorDrawFn fn);
		static InspectorDrawFn GetDrawFunction(std::string name);
	};

	 
	//template<typename T>
	//class ECLIPSED_API ComponentInspectorDrawer
	//{
	//public:
	//	static void DrawInspector(T* comp);
	//};
}

#endif