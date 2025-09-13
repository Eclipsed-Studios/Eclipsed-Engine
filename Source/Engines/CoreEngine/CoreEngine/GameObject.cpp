#include "GameObject.h"

namespace Eclipse
{
	GameObject::GameObject(GameObjectID aId)
		: myID(aId)
	{

	}

	void GameObject::SetName(const std::string& aName)
	{
		myName = aName;
	}

	const std::string& GameObject::GetName() const
	{
		return myName;
	}

	const GameObjectID& GameObject::GetID() const
	{
		return myID;
	}

	GameObject::operator Eclipse::GameObjectID() const
	{
		return myID;
	}
}