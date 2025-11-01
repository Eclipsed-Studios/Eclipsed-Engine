#include "Transform2D.h"

#include "ImGui/ImGui/imgui.h"

#include <sstream>

#include "Utilities/Math/Vector/Vector3.h"

namespace Eclipse
{
	COMPONENT_REGISTRATION(Transform2D);

	void Transform2D::DrawInspector()
	{
		auto globalPosition = GetPosition();

		ImGui::Text("Debug properties");
		ImGui::Text("gobal pos, x: %f, y: %f", globalPosition.x, globalPosition.y);
	}

	void Transform2D::OnSceneLoaded()
	{
		gameObject->transform = this;
	}
	void Transform2D::OnComponentAdded()
	{
		gameObject->transform = this;
	}

	void Transform2D::AddParentTransform(GameObject* aParent, Math::Mat3x3f& aTransform) const
	{
		Transform2D* parentTransform = aParent->GetComponent<Transform2D>();
		if (!parentTransform)
			return;

		Math::Mat3x3f parentTransformMatrix = Math::Mat3x3f::CreateTranslation(parentTransform->GetLocalPosition());
		parentTransformMatrix *= Math::Mat3x3f::CreateRotation(-parentTransform->GetLocalRotation());
		//parentTransformMatrix *= Math::Mat3x3f::CreateScale(parentTransform->GetLocalScale());

		aTransform *= parentTransformMatrix;

		GameObject* parent = aParent->GetParent();
		if (parent)
			AddParentTransform(parent, aTransform);
	}

	Math::Vector2f Transform2D::GetPosition() const
	{
		Math::Mat3x3f mat = GetTransformMatrix();

		Math::Vector3f positionV3(position->x, position->y, 1.f);
		Math::Vector3f positionV3AddedTransform = positionV3 * mat;

		return { positionV3AddedTransform.x, positionV3AddedTransform.y };
	}

	Math::Matrix3x3f Transform2D::GetTransformMatrix() const
	{
		Math::Mat3x3f mat;
		GameObject* parent = gameObject->GetParent();
		if (parent)
			AddParentTransform(parent, mat);

		return mat;
	}

	void Transform2D::AddParentRotation(GameObject* aParent, float& totalRotation) const
	{
		Transform2D* parentTransform = aParent->GetComponent<Transform2D>();
		if (!parentTransform)
			return;

		totalRotation += parentTransform->GetLocalRotation();

		GameObject* parent = aParent->GetParent();
		if (parent)
			AddParentRotation(parent, totalRotation);
	}

	float Transform2D::GetRotation() const
	{
		float rot = rotation;
		GameObject* parent = gameObject->GetParent();
		if (parent)
			AddParentRotation(parent, rot);

		return rot;
	}

	void Transform2D::AddParentScale(GameObject* aParent, Math::Vector2f& totalScale) const
	{
		Transform2D* parentTransform = aParent->GetComponent<Transform2D>();
		if (!parentTransform)
			return;

		totalScale *= parentTransform->GetLocalScale();

		GameObject* parent = aParent->GetParent();
		if (parent)
			AddParentScale(parent, totalScale);
	}

	Math::Vector2f Transform2D::GetScale() const
	{
		Math::Vector2f sca = scale;
		GameObject* parent = gameObject->GetParent();
		if (parent)
			AddParentScale(parent, sca);

		return sca;
	}

	const Math::Vector2f& Transform2D::GetLocalPosition() const
	{
		return position;
	}
	const float Transform2D::GetLocalRotation() const
	{
		return rotation;
	}
	const Math::Vector2f& Transform2D::GetLocalScale() const
	{
		return scale;
	}

	Math::Vector2f* Transform2D::GetPositionPtr()
	{
		return &position.Get();
	}
	float* Transform2D::GetRotationPtr()
	{
		return &rotation.Get();
	}
	Math::Vector2f* Transform2D::GetScalePtr()
	{
		return &scale.Get();
	}

	void Transform2D::SetPosition(const Math::Vector2f& aPosition)
	{
		SetPosition(aPosition.x, aPosition.y);
	}
	void Transform2D::SetPosition(float aX, float aY)
	{
		position->x = aX;
		position->y = aY;

		lastPosition = position;

		myIsDirty = true;
	}

	void Transform2D::SetRotation(float aRotation)
	{
		rotation = aRotation;

		lastRotation = rotation;

		myIsDirty = true;
	}

	void Transform2D::SetScale(const Math::Vector2i& aScale)
	{
		SetScale(static_cast<float>(aScale.x), static_cast<float>(aScale.y));
	}
	void Transform2D::SetScale(const Math::Vector2f& aScale)
	{
		SetScale(aScale.x, aScale.y);
	}
	void Transform2D::SetScale(float aX, float aY)
	{
		scale->x = aX;
		scale->y = aY;

		lastScale = scale;

		myIsDirty = true;
	}

	void Transform2D::AddFunctionToRunOnDirtyUpdate(const std::function<void()>& aFunction)
	{
		myFunctionsToRunOnDirtyUpdate.push_back(aFunction);
	}

	void Transform2D::EditorUpdate()
	{
		if (position->x != lastPosition.x || position->y != lastPosition.y)
			myIsDirty = true;
		if (scale->x != lastScale.x || scale->y != lastScale.y)
			myIsDirty = true;
		if (lastRotation != rotation)
			myIsDirty = true;


		if (myIsDirty)
		{
			for (auto& func : myFunctionsToRunOnDirtyUpdate)
				func();

			myIsDirty = false;
		}
	}
}