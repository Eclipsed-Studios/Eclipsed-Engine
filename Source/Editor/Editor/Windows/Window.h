#pragma once
#include <string>
#include "Random.h"

#include "ImGui/imgui.h"
#include "defines.h"
#include "Editor/WindowRegistry.h"

//#define BASE_WINDOW(type, name)																	\
//public:																							\
//	const std::string windowName = stringify(type);												\
//	const int typeID = std::hash<int>{}(stringify(type));										\
//inline type(const int& aId = -1) : AbstractWindow(aId) {}										\
//virtual AbstractWindow* GetNewWindow(const int& aId = -1) override {return new type(aId); }										\
//private:																						\
//struct AutoRegister {																			\
//	AutoRegister() { ENGINE_NAMESPACE::Editor::WindowRegistry::RegisterWindow<type>(name); }	\
//};																								\
//static inline AutoRegister _register = {};


#define BASE_WINDOW(type, name)																		\
public:																								\
    const size_t typeID = std::hash<std::string>{}(stringify(type));								\
    inline type(const int& aId = -1) : AbstractWindow(name, aId) {}									\
    virtual AbstractWindow* GetNewWindow(const int& aId = -1) override { return new type(aId); }	\
private:																							\
    struct AutoRegister {																			\
        AutoRegister() { ENGINE_NAMESPACE::Editor::WindowRegistry::RegisterWindow<type>(name); }	\
    };																								\
    static inline AutoRegister _register = {};



namespace ENGINE_NAMESPACE::Editor
{
	class AbstractWindow
	{
		friend class WindowManager;

	public:
		AbstractWindow(const std::string& name, const int& aId = -1);

		virtual AbstractWindow* GetNewWindow(const int& aId = -1) { return new AbstractWindow(windowName, aId); }										\


	public:
		virtual void Open() {};
		virtual void Update() {};
		virtual void Close() {};

	public:
		const std::string windowName = "";
		const int instanceID = 0;
		const int typeID = 0;

	protected:
		bool myIsOpen = true;
		bool myWasLastOpen = true;

		ImGuiWindowFlags flags = 0;
	};
}