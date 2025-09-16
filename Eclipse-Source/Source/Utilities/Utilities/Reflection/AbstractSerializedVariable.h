#pragma once

namespace Eclipse { class Component; }
namespace Eclipse::Reflection
{
	class AbstractSerializedVariable
	{
		friend class ReflectionManager;

	public:
		AbstractSerializedVariable(const char* aName, Component* aCompPtr);

	public:
		virtual void* GetData() = 0;
		virtual void ResolveTypeInfo() = 0;

		virtual void DrawInspector() = 0;

		virtual void Resize(const size_t& size) = 0;


	public:
		enum SerializedTypes_
		{
			SerializedType_None,

			SerializedType_String,

			SerializedType_Enum,
			SerializedType_Custom_Type,
			SerializedType_Fundamental,

			SerializedType_List,
			SerializedType_Array,

			SerializedType_Component,
			SerializedType_Gameobject,
		};

	public:
		const char* GetName() const;
		Component* GetComponent();
		const Component* GetComponent() const;
		unsigned GetSizePerElement() const;
		unsigned GetSizeInBytes() const;
		unsigned GetCount() const;
		SerializedTypes_ GetType() const;

	protected:
		const char* name = "";
		Component* pComponent = nullptr;

		SerializedTypes_ type = SerializedType_None;
		unsigned sizePerElement = 0;
		unsigned count = 1;
	};
}