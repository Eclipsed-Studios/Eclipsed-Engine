#include "ReflectedVariable.h"

#include "Reflection/Reflection.h"

namespace Eclipse
{
	AbstractReflectedVariable::AbstractReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent)
		: myName(aName), myTypeName(aTypeName), pComponent(aComponent), myID(Random::GetValue<unsigned>())
	{
		Register();
	}

	void AbstractReflectedVariable::Register()
	{
		Reflection::RegisterVariable(this);
	}
}
