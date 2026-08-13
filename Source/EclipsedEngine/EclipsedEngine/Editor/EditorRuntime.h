#ifdef ECL_EDITOR
#pragma once

#include "EclipsedEngine/EclipsedRuntime.h"

#include "Core/MainSingleton.h"
#include "Core/Files/FileWatcher.h"

namespace Eclipse::Editor
{
	class EditorRuntime
	{
	public:
		bool IsPlaying();

	public:
		void Init(const std::string& path);

	private:
		void SetGameChanged(const FileWatcherEvent&);
		void LoadDLL();

	public:
		void UpdateGame();

		void UpdateEngine();
		void RenderEngine();
		bool BeginFrameEngine();
		void EndFrameEngine();

	public:
		void Shutdown();
		void EnterPlayMode();
		void ExitPlayMode();
		void PauseGame();
		void UnpauseGame();

	private:
		void DrawPlayGameButtons();

	private:
		bool isPlaying = false;
		bool isPaused = false;

		std::atomic<bool> gameChanged{ false };

		EclipsedRuntime eclipseRuntime = {};
	};
}
#endif