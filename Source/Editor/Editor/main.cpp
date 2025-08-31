#include <iostream>

#include "Editor.h"
#include "ErrorCodes.h"

#define LEAN_AND_MEAN
#include <windows.h>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "TemporarySettingsSingleton.h"

#include <chrono>

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

#define performanceTest 0

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	//Utilities::MainSingleton::RegisterInstance<GLFWwindow*>();
	
	TemporarySettingsSingleton::Get().Init(ENGINE_SETTINGS_PATH);
	Editor::EditorContext editor;
	ErrorCode result = editor.Init();

	if (result != ErrorCode::SUCCESS)
		return static_cast<int>(CheckErrorCodes(result));

#if performanceTest

	using clock = std::chrono::high_resolution_clock;
	constexpr int framesToRun = 1000; // number of frames for benchmark
	auto start = clock::now();

	for (int i = 0; i < framesToRun; ++i)
#else
	while (!glfwWindowShouldClose(Utilities::MainSingleton::GetInstance<GLFWwindow*>()))
#endif
	{
		editor.Begin();
		editor.Update();
		editor.Render();
		editor.End();
	}
#if performanceTest
	auto end = clock::now();
	std::chrono::duration<double> elapsed = end - start;

	double totalSeconds = elapsed.count();
	double avgPerFrame = totalSeconds / framesToRun;

	std::cout << "Ran " << framesToRun << " frames in "
			  << totalSeconds << "s\n";
	std::cout << "Average per frame: "
			  << avgPerFrame * 1000.0 << " ms\n";
#endif
	// std::cout << "Window closed succesfully" << std::endl;
}