#pragma once

#include "defines.h"

#include "EclipsedEngine/Components/Component.h"
#include "ECS.hpp"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"

namespace Eclipse
{
	class ECLIPSED_RUNTIME_API Behavior : public Component
	{
	public:
		Behavior();
		virtual ~Behavior();

	public:
		template<typename T>
		T* AddComponent()
		{
			return reinterpret_cast<T*>(
				ECS::AddComponentByName(gameObject->GetID(), typeid(T).name())
				);
		}


	};
}