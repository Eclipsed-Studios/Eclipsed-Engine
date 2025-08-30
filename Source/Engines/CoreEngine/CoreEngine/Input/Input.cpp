#include "Input.h"

#include "GLFW/glfw3.h"

#include "MainSingleton.h"

namespace ENGINE_NAMESPACE
{
	bool Input::GetKey(char aKey)
	{
		return myCurrentKeys[aKey];
	}
	
	bool Input::GetKeyDown(char aKey)
	{
		return myPressedThisFrame[aKey];
	}

	bool Input::GetKeyUp(char aKey)
	{
		return myReleasedThisFrame[aKey];
	}

	void Input::Update()
	{
		myPressedThisFrame = myCurrentKeys & ~myLastKeys;
		myReleasedThisFrame = ~myCurrentKeys & myLastKeys;

		myLastKeys = myCurrentKeys;
	}

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key < 0 || key >= MAX_KEYS) return;

		if (action == GLFW_PRESS) myCurrentKeys[key] = true;
		else if (action == GLFW_RELEASE) myCurrentKeys[key] = false;
	}

	void Input::Init()
	{
		glfwSetKeyCallback(Utilities::MainSingleton::GetInstance<GLFWwindow*>(), KeyCallback);
		//glfwSetMouseCall
	}
}