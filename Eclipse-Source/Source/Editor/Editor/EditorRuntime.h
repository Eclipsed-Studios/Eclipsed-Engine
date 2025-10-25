#pragma once

namespace Eclipse::Editor
{
	class EditorRuntime
	{
	public:
		bool IsPlaying();

	public:
		void UpdateGame();

		void UpdateEngine();
		void RenderEngine();
		bool BeginFrameEngine();
		void EndFrameEngine();

	public:
		void EnterPlayMode();
		void ExitPlayMode();
		void PauseGame();
		void UnpauseGame();

	private:
		void DrawPlayGameButtons();

	private:
		bool isPlaying = false;
		bool isPaused = false;
	};
}