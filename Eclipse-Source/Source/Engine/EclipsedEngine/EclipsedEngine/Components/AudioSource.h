#pragma once

#include <vector>
#include <functional>

#include "EclipsedEngine/Components/Component.h"

#include <CoreEngine/Math/Vector/Vector2.h>

#include "AssetEngine/Assets/AudioClip.h"

namespace Eclipse
{
	namespace Editor
	{
		class InspectorWindow;
	}

	class AudioSource : public Component
	{
		//BASE_SELECTION(AudioSource, 0)

		COMPONENT_FRIEND_CLASS																				\
			BASE_OBJECT_IMPL(type)																				\
	public:																								\
			virtual unsigned GetUpdatePriority() const override { return updatePriority; }						\
			inline type() = default;																			\
			virtual ~type() = default;																			\
			virtual const char* GetComponentName() override { return #type; }							\
	protected:

	public:
		SERIALIZED_FIELD(AudioClip, hitSound);

		void OnDrawInspector() override;

	protected:
		 bool HasDrawInspector() const override { return true; }

	};

}