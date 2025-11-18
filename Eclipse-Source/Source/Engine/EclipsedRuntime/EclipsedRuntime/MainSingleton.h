#pragma once

#include "Runtime_Defines.h"


struct GLFWwindow;

class ECL_RUNTIME_API MainSingleton
{
public:
	struct GLFWwindow* GetWindow();
};

ECL_RUNTIME_API MainSingleton& GetMainSingleton();