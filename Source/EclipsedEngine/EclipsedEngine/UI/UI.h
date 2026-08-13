#pragma once

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
    enum UIWindowFlags_
    {
        UIWindowFlags_None = 0,
        UIWindowFlags_NoTitleBar = 1 << 0,   // Disable title-bar
        UIWindowFlags_NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
        UIWindowFlags_NoMove = 1 << 2,   // Disable user moving the window
        UIWindowFlags_NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
        UIWindowFlags_NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
        UIWindowFlags_NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
        UIWindowFlags_AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
        UIWindowFlags_NoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
        UIWindowFlags_NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
        UIWindowFlags_NoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
        UIWindowFlags_MenuBar = 1 << 10,  // Has a menu-bar
        UIWindowFlags_HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
        UIWindowFlags_NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
        UIWindowFlags_NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
        UIWindowFlags_AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
        UIWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
        UIWindowFlags_NoNavInputs = 1 << 16,  // No keyboard/gamepad navigation within the window
        UIWindowFlags_NoNavFocus = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by Ctrl+Tab)
        UIWindowFlags_UnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
        UIWindowFlags_NoDocking = 1 << 19,  // Disable docking of this window
        UIWindowFlags_NoNav = UIWindowFlags_NoNavInputs | UIWindowFlags_NoNavFocus,
        UIWindowFlags_NoDecoration = UIWindowFlags_NoTitleBar | UIWindowFlags_NoResize | UIWindowFlags_NoScrollbar | UIWindowFlags_NoCollapse,
        UIWindowFlags_NoInputs = UIWindowFlags_NoMouseInputs | UIWindowFlags_NoNavInputs | UIWindowFlags_NoNavFocus,
    };

    typedef int UIWindowFlags;       // -> enum UIWindowFlags_     // Flags: for Begin(), BeginChild()


	class ECL_API UI
	{
    public:
		void Begin(const char* name, bool* isOpen = nullptr, UIWindowFlags flags = 0);
        void End();

        void Text(const char* text);
	};
}