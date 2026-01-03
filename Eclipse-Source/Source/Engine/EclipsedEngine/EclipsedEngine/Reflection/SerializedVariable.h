#pragma once

#include "AbstractSerializedVariable.h"

class EditorReflectionDrawHelper;


namespace Eclipse::Reflection
{
	template<typename T>
	class SerializedVariable final : public AbstractSerializedVariable
	{
		friend class EditorReflectionDrawHelper;

	public:

		//#ifdef ECLIPSED_EDITOR
		SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector);
		SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, const T& aDefaultValue);

		SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, T _min, T _max);
		SerializedVariable(const char* aName, Component* aCompPtr, bool drawInspector, const T& aDefaultValue, T _min, T _max);
		//#else
		//		SerializedVariable(const char* aName, Component* aCompPtr);
		//		SerializedVariable(const char* aName, Component* aCompPtr, const T& aDefaultValue);
		//#endif

		//#ifdef ECLIPSED_EDITOR
		void DrawInspector() override;

		template<typename U>
		void DrawElement(U& element);

		template<typename U>
		void DrawString(U& element);
		//#endif

		int GetImGuiType() const override;

	public:
		void* GetRawData() override;
		void* GetData() override;

		const void* GetData()const override;
		void ResolveTypeInfo() override;
		void Resize(const size_t& size) override;

	public:
		T& Get() { return data; }
		const T& Get() const { return data; }

		void SetData(const T& aValue) { data = aValue; }

		operator T& () { return data; }
		operator const T& () const { return data; }

		T* operator->() { return &data; }
		const T* operator->() const { return &data; }

		SerializedVariable<T>& operator=(const T& aValue) noexcept
		{
			data = aValue;
			hasData = true;
			return *this;
		}

		unsigned GetReplicationID()
		{
			return ReplicatedVariableIndex;
		}

		// Is 0 if not replicated
		unsigned ReplicatedVariableIndex = 0;

	private:
		T data;

		//#ifdef ECLIPSED_EDITOR
		T myMin, myMax;
		bool hasMinMax = false;
	
		bool isDrawn = false;
		//#endif
	};
}

#include "SerializedVariable.inl"