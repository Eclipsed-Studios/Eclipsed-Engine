#pragma once

#ifdef ECL_EDITOR

#include "EclipsedEngine.Core.hpp"
#include <unordered_map>
#include <string>



#define REGISTER_INSPECTOR(cls)																						\
		struct cls##_inspector_registrar																			\
		{																											\
			cls##_inspector_registrar() 																			\
			{																										\
				Eclipse::Editor::ComponentInspectorRegistry::RegisterInspector(										\
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

	class ECL_API ComponentInspectorRegistry
	{
	public:
		static std::unordered_map<std::string, InspectorDrawFn>& Registry();

		static bool InspectorExists(const std::string& name);
		static void RegisterInspector(const std::string& name, InspectorDrawFn fn);
		static InspectorDrawFn GetDrawFunction(const std::string& name);
	};

	 
	//template<typename T>
	//class ECL_API ComponentInspectorDrawer
	//{
	//public:
	//	static void DrawInspector(T* comp);
	//};
}

#endif