#pragma once

#include <string>
#include "Reflection.h"

namespace ENGINE_NAMESPACE
{
	class Component;
	class AbstractReflectedVariable
	{
		friend class Reflection;

	public:
		AbstractReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent);

	public:
		const std::string& GetName() const { return myName; }
		const std::string& GetTypeName() const { return myTypeName; }
		Component* GetComponent() { return pComponent; }

	public:
		virtual void DrawInspector() = 0;

	private:
		void Register();

	private:
		const std::string myName = "";
		const std::string myTypeName = "";
		Component* pComponent = nullptr;
		const unsigned myID = 0;

		bool myWasRegistered = false;
	};

	template<typename T>
	class ReflectedVariable : public AbstractReflectedVariable
	{
	public:
		ReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent)
			: AbstractReflectedVariable(aName, aTypeName, aComponent), myData({})
		{
		}

		ReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent, const T& aDefaultValue)
			: AbstractReflectedVariable(aName, aTypeName, aComponent), myData(aDefaultValue)
		{
		}

		void DrawInspector() override;

	public:
		operator T& () { return myData; }
		operator const T& () const { return myData; }

		ReflectedVariable<T>& operator=(const T& aValue) noexcept
		{
			myData = aValue;
			return *this;
		}

	private:
		T myData = {};
	};
}

namespace ENGINE_NAMESPACE
{
	template<typename T>
	inline void ReflectedVariable<T>::DrawInspector()
	{
		ImGui::Text(GetName().c_str());
		ImGui::SameLine();
		if constexpr (std::is_same<T, float>::value) ImGui::InputFloat(std::string("##float##" + GetName()).c_str(), &myData);
	}
}