#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "TemporarySettingsSingleton.h"

using namespace ENGINE_NAMESPACE;

ErrorCode CheckErrorCodes(ErrorCode aErrorCode)
{
	switch (aErrorCode)
	{
	case ErrorCode::GLFW_FAILED_TO_INITILIZE:
	{
		std::cout << "GLFW failed to initilize" << std::endl;
		glfwTerminate();
		return ErrorCode::FAILED;
	}
	break;
	case ErrorCode::GLFW_WINDOW_FAILED_TO_CREATE:
	{
		std::cout << "GLFW window was not able to be created" << std::endl;
		glfwTerminate();
		return ErrorCode::FAILED;
	}
	break;
	case ErrorCode::GLAD_FAILED_TO_INITILIZE:
	{
		std::cout << "GLAD failed to initilize" << std::endl;
		glfwTerminate();
		return ErrorCode::FAILED;
	}
	break;
	}

	return ErrorCode::SUCCESS;
}

int main()
{
	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);

	Editor editor;

	ErrorCode result = editor.Init();

	if (result != ErrorCode::SUCCESS)
		return static_cast<int>(CheckErrorCodes(result));

	while (!glfwWindowShouldClose(TemporarySettingsSingleton::Get().myWindow))
	{
		editor.Begin();
		editor.Update();
		editor.Render();
		editor.End();
	}

	std::cout << "Window closed succesfully" << std::endl;
}