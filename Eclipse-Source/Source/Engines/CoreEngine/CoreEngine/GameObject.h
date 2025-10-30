#pragma once

#include <string>
#include "ECS/ComponentManager.h"

#include "Utilities/Math/Vector/Vector4.h"

namespace Eclipse
{
	typedef unsigned GameObjectID;

	class ComponentManager;
	class GameObject
	{
		friend class ComponentManager;

	public:
		GameObject(GameObjectID aId);

	public:
		template<typename T>
		T* AddComponent();

		template<typename T>
		T* GetComponent();

		const Math::Vector4f& GetPixelPickingIDColor() { return myPixelPickColor; }

		GameObject*& GetParent();
		void SetParent(GameObject* aGO);
		
		GameObject*& GetChild(int index);
		std::vector<GameObject*>& GetChildren();
		void AddChild(GameObject*& aChild);
		size_t GetChildCount();

		size_t GetChildIndex();
		void SetChildIndex(size_t index);

	public:
		void SetName(const std::string& aName);
		const std::string& GetName() const;

		GameObjectID GetID() const;

		operator Eclipse::GameObjectID() const;

		class Transform2D* transform;

	private:
		GameObject* parent = nullptr;
		std::vector<GameObject*> children;
		size_t myChildIndex = 0;
	
		GameObjectID myID;
		std::string myName = "Gameobject";

		Math::Vector4f myPixelPickColor;
	};

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		return ComponentManager::template AddComponent<T>(myID);
	}

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		return ComponentManager::template GetComponent<T>(myID);
	}
}