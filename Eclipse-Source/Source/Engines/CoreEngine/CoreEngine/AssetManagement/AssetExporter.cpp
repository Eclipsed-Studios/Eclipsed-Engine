#include "AssetExporter.h"

#include <fstream>
#include <filesystem>
#include <map>
#include <functional>

namespace Eclipse
{
	void AssetExporter::ExportAll()
	{
        using namespace std::filesystem;

        std::vector<FileInfo> files;
        for (auto& entry : recursive_directory_iterator(ASSET_PATH))
        {
            if (entry.is_directory()) continue;
            files.push_back(Resources::GetFileInfo(entry));
        }

        std::sort(files.begin(), files.end(),
            [](const FileInfo& a, const FileInfo& b) {
                return a.type > b.type;
            });

        std::map<size_t, FileEntry> datas;
        for (FileInfo& file : files)
        {
            std::ifstream in(file.filePath, std::ios::binary | std::ios::ate);
            if (!in.is_open()) continue;

            std::string relativePath = std::filesystem::relative(file.filePath, SOURCE_PATH).generic_string();
            size_t id = std::hash<std::string>{}(relativePath);
            FileEntry& entry = datas[id];

            entry.info = file;

            std::streamsize size = in.tellg();
            in.seekg(0, std::ios::beg);
            entry.data.resize(size);
            in.read(reinterpret_cast<char*>(entry.data.data()), size);
        }


        std::ofstream out(SOURCE_PATH "Bin/assets.bundle", std::ios::binary);
        if (!out.is_open()) return;

        const unsigned fileCount = static_cast<unsigned>(datas.size());
        out.write(reinterpret_cast<const char*>(&fileCount), sizeof(unsigned));

        size_t baseOffset = sizeof(unsigned) + datas.size() * sizeof(FileEntryData);
        size_t currentOffset = baseOffset;
        for (auto& [id, entry] : datas) {
            entry.offset = currentOffset;
            currentOffset += entry.data.size();
        }

        for (auto& [id, entry] : datas)
        {
            size_t size = entry.data.size();
            out.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
            out.write(reinterpret_cast<const char*>(&entry.offset), sizeof(size_t));
            out.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
        }

        // Write raw file data
        for (auto& [id, entry] : datas)
        {
            out.write(reinterpret_cast<const char*>(entry.data.data()), entry.data.size());
        }

        out.close();
	}
}


