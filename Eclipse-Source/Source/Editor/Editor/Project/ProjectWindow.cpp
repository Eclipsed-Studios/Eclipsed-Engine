#include "ProjectWindow.h"

#include <windows.h>
#include <shobjidl.h> 

namespace Eclipse::Editor
{
	void ProjectSettingsWindow::Update()
	{
        ImGui::Text(currentPath.c_str());
        if (ImGui::Button("Select Path")) currentPath = SelectProjectPath();
	}

    std::string ProjectSettingsWindow::SelectProjectPath()
	{
        std::string folderPath;
        IFileDialog* pFileDialog = nullptr;
        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog));
        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            pFileDialog->GetOptions(&dwOptions);
            pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS);

            hr = pFileDialog->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                if (SUCCEEDED(pFileDialog->GetResult(&pItem)))
                {
                    PWSTR pszFilePath = nullptr;
                    if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
                    {
                        char buffer[MAX_PATH];
                        wcstombs(buffer, pszFilePath, MAX_PATH);
                        folderPath = buffer;
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileDialog->Release();
        }
        set

        return folderPath;
	}
}
