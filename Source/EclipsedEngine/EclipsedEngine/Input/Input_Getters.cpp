#include "pch.h"

#include "AbstractInput.h"

namespace Eclipse::Input
{
	bool AbstractInput::GetKey(int aKey)
	{
		return currentKeys[aKey];
	}

	bool AbstractInput::GetKey(char aKey)
	{
		return currentKeys[aKey];
	}

	bool AbstractInput::GetKey(Keycode::Scancode aKey)
	{
		return currentKeys[(int)aKey];
	}



	bool AbstractInput::GetKeyDown(int aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool AbstractInput::GetKeyDown(char aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool AbstractInput::GetKeyDown(Keycode::Scancode aKey)
	{
		return pressedThisFrame[(int)aKey];
	}



	bool AbstractInput::GetKeyUp(int aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool AbstractInput::GetKeyUp(char aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool AbstractInput::GetKeyUp(Keycode::Scancode aKey)
	{
		return releasedThisFrame[(int)aKey];
	}

	bool AbstractInput::GetAny()
	{
		return currentKeys.any();
	}

	Keycode::Scancode AbstractInput::GetAnyKey()
	{
		for (int i = 0; i < currentKeys.size(); i++)
			if (currentKeys[i])
				return static_cast<Keycode::Scancode>(i);

		return Keycode::Scancode::NONE;
	}


	bool AbstractInput::GetMouse(int aKey)
	{
		return currentKeys[aKey];
	}

	bool AbstractInput::GetMouse(Keycode::Scancode aKey)
	{
		return currentKeys[(int)aKey];
	}



	bool AbstractInput::GetMouseDown(int aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool AbstractInput::GetMouseDown(Keycode::Scancode aKey)
	{
		return pressedThisFrame[(int)aKey];
	}



	bool AbstractInput::GetMouseUp(int aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool AbstractInput::GetMouseUp(Keycode::Scancode aKey)
	{
		return releasedThisFrame[(int)aKey];
	}

	const Math::Vector2f& AbstractInput::GetGameMousePos()
	{
		return currentGamePos;
	}

	const Math::Vector2i& AbstractInput::GetMousePos()
	{
		return currentPos;
	}

	const Math::Vector2i& AbstractInput::GetMouseDeltaPos()
	{
		return mouseDeltaPos;
	}

	const Math::Vector2i& AbstractInput::GetScroll()
	{
		return mouseScrollDelta;
	}

	const Math::Vector2i& AbstractInput::GetNormalizedScroll()
	{
		return normalizedMouseScrollDelta;
	}





	bool AbstractInput::IsWindowFocused()
	{
		return windowFocused;
	}

	bool AbstractInput::IsMouseInside()
	{
		return mouseIsInside;
	}














	// should not be in getter but rahter setters
	void AbstractInput::SetMousePositionEditor(const Math::Vector2f& aPosition)
	{
		currentGamePos = aPosition;
	}
}
