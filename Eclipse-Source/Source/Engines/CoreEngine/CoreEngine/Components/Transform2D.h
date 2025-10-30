#pragma once

#include <vector>
#include <functional>

#include "CoreEngine/ECS/ComponentManager.h"
#include "Base/BaseComponent.h"

#include <Utilities/Math/Vector/Vector2.h>

namespace Eclipse
{
	class Transform2D : public Component
	{
		BASE_SELECTION(Transform2D, UINT_MAX / 2)

	public:
		void DrawInspector() override;

		void OnSceneLoaded() override;
		void OnComponentAdded() override;

		void EditorUpdate() override;

		
		void AddParentTransform(GameObject* aParent, Math::Vector2f& aPosition) const;

		//Global sorta
		Math::Vector2f GetPosition() const;
		float GetRotation() const;
		Math::Vector2f GetScale() const;

		//Local
		const Math::Vector2f& GetLocalPosition() const;
		const float GetLocalRotation() const;
		const Math::Vector2f& GetLocalScale() const;

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

		Math::Vector2f lastPosition;
		float lastRotation;
		Math::Vector2f lastScale;

	private:
		bool myIsDirty = true;
		std::vector<std::function<void()>> myFunctionsToRunOnDirtyUpdate;
	};
}