#pragma once

#include "Editor/Views/AbstractView.h"

namespace Eclipse::Editor
{
	class AssetBrowserView final : public AbstractView
	{
		VIEW_IMPL(AssetBrowserView, "Asset Browser", "", 0)
	};
}