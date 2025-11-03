#pragma once

namespace Eclipse::Editor
{
	class EditorUIManager final
	{
	public:
		void Init();

		void BeginFrame();
		void Update();
		void Render();
		void EndFrame();

	private:
		void LoadFonts();

		WindowManager myWindowManager;

	public:
		static inline ImFont* FontTiny = nullptr;
		static inline ImFont* FontExtraSmall = nullptr;
		static inline ImFont* FontSmall = nullptr;
		static inline ImFont* FontMedium = nullptr;
		static inline ImFont* FontLarge = nullptr;
		static inline ImFont* FontExtraLarge = nullptr;
	};
}