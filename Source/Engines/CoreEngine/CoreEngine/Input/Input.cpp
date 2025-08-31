#include "Input.h"

#include "GLFW/glfw3.h"

#include "MainSingleton.h"
#include "DebugLogger.h"

namespace ENGINE_NAMESPACE
{
	void Input::Update()
	{
		// Mouse delta
		mouseScrollDelta = Math::Vector2i(0, 0);
		normalizedMouseScrollDelta = Math::Vector2i(0, 0);

		// Mouse pos 
		mouseDeltaPos = currentPos - lastPos;
		lastPos = currentPos;

		// Buttons (keyboard and mouse buttons)
		pressedThisFrame = currentKeys & ~lastKeys;
		releasedThisFrame = ~currentKeys & lastKeys;

		lastKeys = currentKeys;
	}


	void Input::Init()
	{
		GLFWwindow* window = Utilities::MainSingleton::GetInstance<GLFWwindow*>();

		glfwSetKeyCallback(window, OnKey_Callback);
		glfwSetCursorPosCallback(window, OnMousePos_Callback);
		glfwSetCursorEnterCallback(window, OnMouseEnter_Callback);
		glfwSetMouseButtonCallback(window, OnMouseButton_Callback);
		glfwSetWindowFocusCallback(window, OnWindowFocus_Callback);
		glfwSetScrollCallback(window, OnMouseScroll_Callback);
	}
}