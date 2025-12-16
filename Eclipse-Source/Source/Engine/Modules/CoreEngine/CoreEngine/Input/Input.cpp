#include "pch.h"

#include "Input.h"

#include "OpenGL/GLFW/glfw3.h"

#include "InputMapper.h"

namespace Eclipse
{
	std::bitset<MAX_KEYS> Input::zeroKeys;
	std::bitset<MAX_KEYS> Input::currentKeys;
	std::bitset<MAX_KEYS> Input::lastKeys;
	std::bitset<MAX_KEYS> Input::pressedThisFrame;
	std::bitset<MAX_KEYS> Input::releasedThisFrame;
	Math::Vector2i Input::currentGamePos;
	Math::Vector2i Input::currentPos;
	Math::Vector2i Input::lastPos;
	Math::Vector2i Input::mouseDeltaPos;
	Math::Vector2i Input::mouseScrollDelta;
	Math::Vector2i Input::normalizedMouseScrollDelta;
	bool Input::mouseIsInside = false;
	bool Input::windowFocused = false;

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

		GLFWwindow* window = MainSingleton::GetInstance<GLFWwindow*>();

		//glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnKey_Callback(w, key, scancode, action, mods);
		//	});

		//glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnMousePos_Callback(w, x, y);
		//	});

		//glfwSetCursorEnterCallback(window, [](GLFWwindow* w, int entered) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnMouseEnter_Callback(w, entered);
		//	});

		//glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnMouseButton_Callback(w, button, action, mods);
		//	});

		//glfwSetWindowFocusCallback(window, [](GLFWwindow* w, int focused) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnWindowFocus_Callback(w, focused);
		//	});

		//glfwSetScrollCallback(window, [](GLFWwindow* w, double xOffset, double yOffset) {
		//	Utilities::MainSingleton::GetInstance<Input>().OnMouseScroll_Callback(w, xOffset, yOffset);
		//	});














		glfwSetKeyCallback(window, OnKey_Callback); 

		glfwSetCursorPosCallback(window, OnMousePos_Callback);

		glfwSetCursorEnterCallback(window, OnMouseEnter_Callback);

		glfwSetMouseButtonCallback(window, OnMouseButton_Callback);

		glfwSetWindowFocusCallback(window, OnWindowFocus_Callback);

		glfwSetScrollCallback(window, OnMouseScroll_Callback);
	}
}