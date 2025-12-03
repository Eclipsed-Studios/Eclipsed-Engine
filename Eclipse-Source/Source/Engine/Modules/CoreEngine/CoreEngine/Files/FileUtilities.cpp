#include "pch.h"

#include "FileUtilities.h"
#include <windows.h>
#include <shobjidl.h>
#include <string>

std::string Eclipse::Files::SelectFolderDialog()
{
    std::string result;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileDialog* pFileDialog = nullptr;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog));

        if (SUCCEEDED(hr)) {
            DWORD options = 0;
            pFileDialog->GetOptions(&options);
            pFileDialog->SetOptions(options | FOS_PICKFOLDERS); // Folder mode

            hr = pFileDialog->Show(NULL);
            if (SUCCEEDED(hr)) {
                IShellItem* pItem = nullptr;
                hr = pFileDialog->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath = NULL;
                    pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Convert from wide string (UTF-16) to UTF-8 std::string
                    if (pszFilePath) {
                        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, NULL, 0, NULL, NULL);
                        std::string path(sizeNeeded - 1, 0); // exclude null terminator
                        WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, &path[0], sizeNeeded, NULL, NULL);
                        result = path;

                        CoTaskMemFree(pszFilePath);
                    }

                    pItem->Release();
                }
            }
            pFileDialog->Release();
        }
        CoUninitialize();
    }

    return result; // empty if cancelled
}
