#include "Input.h"

#include "GLFW/glfw3.h"
#include <algorithm>

namespace ENGINE_NAMESPACE
{
	void Input::OnMousePos_Callback(GLFWwindow* window, double x, double y)
	{
		memcpy(&currentPos.x, &x, sizeof(int));
		memcpy(&currentPos.y, &y, sizeof(int));
	}

	void Input::OnMouseEnter_Callback(GLFWwindow* window, int entered)
	{
		mouseIsInside = (bool)entered;
	}

	void Input::OnMouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) currentKeys[button] = true;
		else if (action == GLFW_RELEASE) currentKeys[button] = false;
	}

	void Input::OnWindowFocus_Callback(GLFWwindow* window, int focused)
	{
		windowFocused = focused;
	}

	void Input::OnMouseScroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
	{
		mouseScrollDelta.x += xOffset;
		mouseScrollDelta.y += yOffset;

		normalizedMouseScrollDelta.x = std::clamp(mouseScrollDelta.x, -1, 1);
		normalizedMouseScrollDelta.y = std::clamp(mouseScrollDelta.y, -1, 1);
	}

	void Input::OnKey_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key < 0 || key >= MAX_KEYS) return;

		if (action == GLFW_PRESS) currentKeys[key] = true;
		else if (action == GLFW_RELEASE) currentKeys[key] = false;
	}
}