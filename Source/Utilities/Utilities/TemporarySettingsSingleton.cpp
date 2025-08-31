#include "TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    void TemporarySettingsSingleton::SetWindowTitle(const char *aWindowTitle)
    {
        glfwSetWindowTitle(Utilities::MainSingleton::GetInstance<GLFWwindow *>(), aWindowTitle);
        myCreatedGameTitle = aWindowTitle;
    }
}