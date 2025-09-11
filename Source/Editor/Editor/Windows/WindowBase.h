#include "Window.h"	

/**
* @brief BASE_SELECTION will do different things depending on the amount of arguments passed.
* @param BASE_SELECTION(Type Name)
* @param BASE_SELECTION(Type Name Category) ### Category can be "1/2/3" must be split with '/'.
*/
#define HELP

#define BASE_MACRO_NAME EDITOR_WINDOW_BASE
#include "MacroOverloadSelector.h"	

#define EDITOR_WINDOW_BASE_2(type, name)                                           \
public:                                                                             \
    const size_t typeID = std::hash<std::string>{}(#type);                          \
    inline type(const int& aId = -1) : AbstractWindow(name, aId) {}                \
    virtual AbstractWindow* GetNewWindow(const int& aId = -1) override {           \
        return new type(aId);                                                      \
    }                                                                              \
private:                                                                            \
    struct AutoRegister {                                                           \
        AutoRegister() {                                                            \
            Eclipse::Editor::WindowRegistry::RegisterWindow<type>(name); \
        }                                                                          \
    };                                                                             \
    static inline AutoRegister _register = {};


#define EDITOR_WINDOW_BASE_3(type, name, category)           \
public:                                                       \
    const char* GetCategoryName() override { return category; } \
    EDITOR_WINDOW_BASE_2(type, name)