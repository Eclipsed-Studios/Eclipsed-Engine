#pragma once

namespace Eclipse::Editor
{
	class MainMenuBar final
	{
	public:
		static void Init();
		static void Update();

	private:
		static void DrawViews();
	};
}