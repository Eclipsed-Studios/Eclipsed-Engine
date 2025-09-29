#include "TemporarySettingsSingleton.h"

// #define GLFW_INCLUDE_NONE
// #include "GLFW/glfw3.h"

namespace Eclipse
{
    void TemporarySettingsSingleton::SetWindowTitle(const char* aWindowTitle)
    {
        //glfwSetWindowTitle(Utilities::MainSingleton::GetInstance<GLFWwindow *>(), aWindowTitle);
        myCreatedGameTitle = aWindowTitle;
    }
}