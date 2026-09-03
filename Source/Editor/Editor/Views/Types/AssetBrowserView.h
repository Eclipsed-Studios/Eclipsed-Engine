#pragma once

#include "ImGui/imgui.h"

#include "ViewRegistry.h"

#define VIEW_IMPL(type, name, category, flags)						\
public:																\
inline type() : AbstractView(name, category, true, flags) {}		\
inline static void* GetNew() { return new type; }					\
private:															\
	struct AutoRegister {											\
		AutoRegister() {											\
			ViewRegistry::RegisterView(#type, &type::GetNew);	\
	}																\
};																	\
static inline AutoRegister _register = {};

namespace Eclipse::Editor
{
	class AbstractView
	{
	public:
		AbstractView(const char* _name, const char* _category, bool _isOpen, ImGuiWindowFlags _flags);

	public:
		virtual void Open() {};

		virtual void PreUpdate() {};
		virtual void Update() {};
		virtual void PostUpdate() {};

		virtual void Close() {};

	public:
		const char* GetName() const;
		ImGuiWindowFlags GetFlags() const;
		bool* GetIsOpenPtr();
		bool GetIsOpen() const;
		int GetID() const;

	private:
		int id = 0;

		ImGuiWindowFlags flags;
		const char* name;
		const char* category;
		bool isOpen = true;
	};
}