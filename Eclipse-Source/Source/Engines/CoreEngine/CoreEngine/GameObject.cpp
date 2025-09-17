#include "GameObject.h"

namespace Eclipse
{
	GameObject::GameObject(GameObjectID aId)
		: myID(aId)
	{
		Math::Vector4i colorInt;
		
		colorInt.x = (myID & 0x000000FF) >> 0;
		colorInt.y = (myID & 0x0000FF00) >> 8;
		colorInt.z = (myID & 0x00FF0000) >> 16;
		colorInt.w = 1;

		myPixelPickColor = Math::Vector4f(colorInt.x / 255.f, colorInt.y / 255.f, colorInt.z / 255.f, 1);
	}

	void GameObject::SetName(const std::string& aName)
	{
		myName = aName;
	}

	const std::string& GameObject::GetName() const
	{
		return myName;
	}

	GameObjectID GameObject::GetID() const
	{
		return myID;
	}

	GameObject::operator Eclipse::GameObjectID() const
	{
		return myID;
	}
}