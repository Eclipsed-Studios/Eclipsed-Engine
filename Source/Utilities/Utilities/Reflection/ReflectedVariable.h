#pragma once

#include <string>
#include "Reflection.h"

namespace Eclipse
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
		virtual void* GetData() { return nullptr; }
		unsigned GetSize() { return size; }

	public:
		virtual void DrawInspector() = 0;

	private:
		void Register();

	protected:
		const std::string myName = "";
		const std::string myTypeName = "";
		Component* pComponent = nullptr;
		const unsigned myID = 0;
		unsigned size = 0;

		bool myWasRegistered = false;
	};

	template<typename T>
	class ReflectedVariable : public AbstractReflectedVariable
	{
	public:
		ReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent)
			: AbstractReflectedVariable(aName, aTypeName, aComponent), myData({})
		{
			size = sizeof(T);
		}

		ReflectedVariable(const std::string& aName, const std::string& aTypeName, Component* aComponent, const T& aDefaultValue)
			: AbstractReflectedVariable(aName, aTypeName, aComponent), myData(aDefaultValue)
		{
			if constexpr (std::is_same<T, std::string>::value) size = aDefaultValue.size();
			else size = sizeof(T);
		}

		void DrawInspector() override;

		T& Get() { return myData; }
		const T& Get() const { return myData; }

		void* GetData() override { return &myData; }

	public:
		operator T& () { return myData; }
		operator const T& () const { return myData; }

		ReflectedVariable<T>& operator=(const T& aValue) noexcept
		{
			if constexpr (std::is_same<T, std::string>::value) size = aValue.size();

			myData = aValue;
			return *this;
		}

		T* operator->() { return &myData; }
		const T* operator->() const { return &myData; }

	private:
		T myData = {};
	};
}

namespace Eclipse
{
	template<typename T>
	inline void ReflectedVariable<T>::DrawInspector()
	{
		ImGui::Text(GetName().c_str());
		ImGui::SameLine();
		if constexpr (std::is_same<T, float>::value) ImGui::DragFloat(std::string("##float##" + GetName()).c_str(), &myData, 0.01f);
	}
}