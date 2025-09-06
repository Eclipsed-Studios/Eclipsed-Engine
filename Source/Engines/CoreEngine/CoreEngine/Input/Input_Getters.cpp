#include "Input.h"

namespace ENGINE_NAMESPACE
{
	bool Input::GetKey(int aKey)
	{
		return currentKeys[aKey];
	}

	bool Input::GetKey(char aKey)
	{
		return currentKeys[aKey];
	}

	bool Input::GetKey(Keycode aKey)
	{
		return currentKeys[(int)aKey];
	}



	bool Input::GetKeyDown(int aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool Input::GetKeyDown(char aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool Input::GetKeyDown(Keycode aKey)
	{
		return pressedThisFrame[(int)aKey];
	}



	bool Input::GetKeyUp(int aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool Input::GetKeyUp(char aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool Input::GetKeyUp(Keycode aKey)
	{
		return releasedThisFrame[(int)aKey];
	}



	bool Input::GetMouse(int aKey)
	{
		return currentKeys[aKey];
	}

	bool Input::GetMouse(MouseButton aKey)
	{
		return currentKeys[(int)aKey];
	}



	bool Input::GetMouseDown(int aKey)
	{
		return pressedThisFrame[aKey];
	}

	bool Input::GetMouseDown(MouseButton aKey)
	{
		return pressedThisFrame[(int)aKey];
	}



	bool Input::GetMouseUp(int aKey)
	{
		return releasedThisFrame[aKey];
	}

	bool Input::GetMouseUp(MouseButton aKey)
	{
		return releasedThisFrame[(int)aKey];
	}


	const Math::Vector2i& Input::GetMousePos()
	{
		return currentPos;
	}

	const Math::Vector2i& Input::GetMouseDeltaPos()
	{
		return mouseDeltaPos;
	}

	const Math::Vector2i& Input::GetScroll()
	{
		return mouseScrollDelta;
	}

	const Math::Vector2i& Input::GetNormalizedScroll()
	{
		return normalizedMouseScrollDelta;
	}





	bool Input::IsWindowFocused()
	{
		return windowFocused;
	}

	bool Input::IsMouseInside()
	{
		return mouseIsInside;
	}
}