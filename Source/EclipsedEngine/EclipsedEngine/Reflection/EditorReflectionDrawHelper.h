#pragma once

#include "EclipsedEngine.Core.hpp"
#include "EclipsedEngine/Reflection/SerializedVariable.h"

namespace Eclipse::Reflection
{
	template<typename T>
	class SerializedVariable;
}

class ECL_API EditorReflectionDrawHelper
{
public:
	template<typename T>
	static void DrawReflectedVariable(Eclipse::Reflection::SerializedVariable<T>& var);
};

#include "EditorReflectionDrawHelper.inl"