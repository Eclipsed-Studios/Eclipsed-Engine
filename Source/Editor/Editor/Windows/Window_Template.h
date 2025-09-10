#pragma once

#include "WindowBase.h"

HELP // Hover this for some help.

namespace ENGINE_NAMESPACE::Editor
{
	class TemplateWindow final : public AbstractWindow
	{
		BASE_SELECTION(TemplateWindow, "TemplateWindow");

	public:
		void Open() override {};
		void Update() override {};
		void Close() override {};
	};
}