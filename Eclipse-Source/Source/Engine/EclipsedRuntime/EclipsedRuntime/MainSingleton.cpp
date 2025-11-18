#include "Input.h"

#include "Utilities/Common/MainSingleton.h"
#include "MainSingleton.h"

#include "OpenGL/GLFW/glfw3.h"

static MainSingleton mainSingleton;

ECL_RUNTIME_API MainSingleton& GetMainSingleton()
{
    return mainSingleton;
}

GLFWwindow* MainSingleton::GetWindow()
{
    return Eclipse::Utilities::MainSingleton::GetInstance<GLFWwindow*>();
}
