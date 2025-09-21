#include "AbstractSerializedVariable.h"

#include "Reflection.h"

namespace Eclipse::Reflection
{
	AbstractSerializedVariable::AbstractSerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector)
		: name(aName), pComponent(aCompPtr), canDrawInspector(drawInspector)
	{
		ReflectionManager::RegisterVariable(this);
	}


	const char* AbstractSerializedVariable::GetName() const { return name; }
	std::string AbstractSerializedVariable::GetNameID() const { return std::string("##") + std::string(name); }
	Component* AbstractSerializedVariable::GetComponent() { return pComponent; }
	const Component* AbstractSerializedVariable::GetComponent() const { return pComponent; }
	unsigned AbstractSerializedVariable::GetSizePerElement() const { return sizePerElement; }
	unsigned AbstractSerializedVariable::GetSizeInBytes() const { return sizePerElement * count; }
	unsigned AbstractSerializedVariable::GetCount() const { return count; }
	AbstractSerializedVariable::SerializedTypes_ AbstractSerializedVariable::GetType() const { return type; }
}