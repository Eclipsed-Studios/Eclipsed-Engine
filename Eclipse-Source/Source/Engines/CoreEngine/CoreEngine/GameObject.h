#pragma once

#include <string>
#include "ECS/ComponentManager.h"

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

	public:
		void SetName(const std::string& aName);
		const std::string& GetName() const;

		GameObjectID GetID() const;

		operator Eclipse::GameObjectID() const;


	private:
		GameObjectID myID;
		std::string myName = "Gameobject";
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