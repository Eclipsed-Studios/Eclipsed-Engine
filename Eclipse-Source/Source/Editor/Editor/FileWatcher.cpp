#include "FileWatcher.h"

namespace Eclipse::Editor
{
	void FileWatcher::Start()
	{
		if (started) return;

		started = true;

		std::string assetPath = ASSET_PATH;
		std::wstring wAssetPath(assetPath.begin(), assetPath.end());

		HANDLE hDir = CreateFileW(
			wAssetPath.c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);

		std::thread watcher([hDir]() {
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
						std::string pathString(fileName.begin(), fileName.end());
						pathString.insert(0, ASSET_PATH);

						FileInfo finfo = Resources::GetFileInfo(pathString);

						switch (info->Action)
						{
						case FILE_ACTION_ADDED:
							HandleEvent(EventType::FileAdded, pathString);
							break;
						case FILE_ACTION_REMOVED:
							HandleEvent(EventType::FileRemoved, pathString);
							break;
						case FILE_ACTION_MODIFIED:
							HandleEvent(EventType::Modified, pathString);
							break;
						case FILE_ACTION_RENAMED_OLD_NAME:
							HandleEvent(EventType::RenamedOld, pathString);
							break;
						case FILE_ACTION_RENAMED_NEW_NAME:
							HandleEvent(EventType::RenamedNew, pathString);
							break;
						}


						if (info->NextEntryOffset != 0)
							info = (FILE_NOTIFY_INFORMATION*)((LPBYTE)info + info->NextEntryOffset);
						else
							info = nullptr;
					} while (info != nullptr);
				}
			}
			});
		watcher.detach();
	}

	void FileWatcher::Subscribe(EventType type, std::function<void(const std::string&)> func)
	{
		subscribedEvents[type].push_back(func);
	}

	void FileWatcher::HandleEvent(EventType event, const std::string& path)
	{
		for (auto& [type, funcList] : subscribedEvents)
		{
			if ((unsigned)type & (unsigned)event)
			{
				for (auto& func : funcList)
				{
					func(path);
				}
			}
		}
	}
}