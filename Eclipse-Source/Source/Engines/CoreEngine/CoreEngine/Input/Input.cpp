#include "Input.h"

#include "GLFW/glfw3.h"

#include "MainSingleton.h"

#include "InputMapper.h"

namespace Eclipse
{
	void Input::Update()
	{
		// Mouse delta
		//mouseScrollDelta = Math::Vector2i(0, 0);
		normalizedMouseScrollDelta = Math::Vector2i(0, 0);

		// Mouse pos 
		mouseDeltaPos = currentPos - lastPos;
		lastPos = currentPos;

		// Buttons (keyboard and mouse buttons)
		pressedThisFrame = currentKeys & ~lastKeys;
		releasedThisFrame = ~currentKeys & lastKeys;

		lastKeys = currentKeys;

		InputMapper::Update();
	}


	void Input::Init()
	{
		InputMapper::Load();

		GLFWwindow* window = Utilities::MainSingleton::GetInstance<GLFWwindow*>();

		glfwSetKeyCallback(window, OnKey_Callback);
		glfwSetCursorPosCallback(window, OnMousePos_Callback);
		glfwSetCursorEnterCallback(window, OnMouseEnter_Callback);
		glfwSetMouseButtonCallback(window, OnMouseButton_Callback);
		glfwSetWindowFocusCallback(window, OnWindowFocus_Callback);
		glfwSetScrollCallback(window, OnMouseScroll_Callback);
	}
}