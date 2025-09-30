#pragma once

#include "Base/BaseComponent.h"

#include "ECS/ComponentManager.h"

#include <Math/Vector/Vector2.h>

#include <vector>
#include <functional>

namespace Eclipse
{
	class Transform2D : public Component
	{
		BASE_SELECTION(Transform2D, UINT_MAX)

	public:

		void OnComponentAdded() override;

		void EditorUpdate() override;

		const Math::Vector2f& GetPosition() const;
		const float GetRotation() const;
		const Math::Vector2f& GetScale() const;

		Math::Vector2f* GetPositionPtr();
		float* GetRotationPtr();
		Math::Vector2f* GetScalePtr();

		void SetPosition(const Math::Vector2f& aPosition);
		void SetPosition(float aX, float aY);

		void SetRotation(float aRotation);

		void SetScale(const Math::Vector2i& aScale);
		void SetScale(const Math::Vector2f& aScale);
		void SetScale(float aX, float aY);

		void AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction);

	private:
		SERIALIZED_FIELD_DEFAULT(Math::Vector2<float>, position, Math::Vector2f(0, 0));
		SERIALIZED_FIELD_DEFAULT(float, rotation, 0);
		SERIALIZED_FIELD_DEFAULT(Math::Vector2f, scale, Math::Vector2f(1, 1));

	private:
		bool myIsDirty = true;
		std::vector<std::function<void()>> myFunctionsToRunOnDirtyUpdate;
	};
}