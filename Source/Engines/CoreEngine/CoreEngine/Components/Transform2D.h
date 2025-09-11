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
		void Update() override;

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

	public:
		virtual rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		virtual void Load(const rapidjson::Value& aValue) override;

		void AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction);

	protected:
		void DrawInspector() override;

    private:
        Math::Vector2f position = {0, 0};
        float rotation = 0;
        Math::Vector2f scale = {1, 1};

		std::vector<std::function<void()>> myFunctionsToRunOnDirtyUpdate;

		bool myIsDirty = true;
	};
}