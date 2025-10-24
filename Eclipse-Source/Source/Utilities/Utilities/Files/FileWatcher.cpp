#include "FileWatcher.h"

namespace Eclipse::Editor
{
	void FileWatcher::WatchPath(WatchedDirectory& aDir)
	{
		std::string assetPath = aDir.watchPath;
		std::wstring wAssetPath(assetPath.begin(), assetPath.end());

		HANDLE hDir = CreateFileW(
			wAssetPath.c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);

		char buffer[1024];
		DWORD bytesReturned;

		while (true)
		{
			if (ReadDirectoryChangesW(
				hDir,
				&buffer,
				sizeof(buffer),
				TRUE,
				FILE_NOTIFY_CHANGE_FILE_NAME |
				FILE_NOTIFY_CHANGE_DIR_NAME |
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				&bytesReturned,
				NULL,
				NULL))
			{
				FILE_NOTIFY_INFORMATION* info = (FILE_NOTIFY_INFORMATION*)buffer;

				do
				{
					std::wstring fileName(info->FileName, info->FileNameLength / sizeof(WCHAR));
					std::string pathString(std::filesystem::path(fileName).string());
					//pathString.insert(0, ASSET_PATH);

					aDir.events.push_back({ pathString, (int)info->Action });

					if (info->NextEntryOffset != 0)
						info = (FILE_NOTIFY_INFORMATION*)((LPBYTE)info + info->NextEntryOffset);
					else
						info = nullptr;
				} while (info != nullptr);
			}
		}
	}

	void FileWatcher::Subscribe(const std::string& aPath, std::function<void(const FileWatcherEvent&)> func)
	{
		std::lock_guard<std::mutex> lock(watchedDirectoriesMutex);

		WatchedDirectory& dir = watchedDirectories[aPath];

		dir.onChangedEvent = func;
		dir.thread  = std::thread(&FileWatcher::WatchPath, std::ref(watchedDirectories[aPath]));
		dir.watchPath = aPath;
		dir.thread.detach();
	}

	void FileWatcher::Unsubscribe(const std::string& name)
	{
		if (watchedDirectories.find(name) == watchedDirectories.end()) return;

		watchedDirectories[name].thread.join();
		watchedDirectories.erase(name);
	}

	void FileWatcher::InvokeEvents()
	{
		std::lock_guard<std::mutex> lock(watchedDirectoriesMutex);

		for (auto& [path, dir] : watchedDirectories)
		{
			for (auto& event : dir.events)
			{
				dir.onChangedEvent(event);
			}

			dir.events.clear();
		}
	}

}