#pragma once

#include <filesystem>
#include "FileInfo.h"

namespace Eclipse::Utilities
{
	struct Directory {
		FileInfo path;
		
		std::vector<std::shared_ptr<Directory>> subDirectories;
		std::vector<FileInfo> files;
	};

	class DirectoryTree final
	{
	public:
		DirectoryTree() = default;
		DirectoryTree(const std::filesystem::path& iteration_path);

	public:
		const Directory* GetRoot() const;
		Directory* GetRoot();

		const Directory* GetDirectoryFromPath(const std::filesystem::path& directory_path) const;
		Directory* GetDirectoryFromPath(const std::filesystem::path& directory_path);

		const FileInfo& GetRootPath() const;
		
	private:
		void Internal_IterateItems(const std::filesystem::path& start_path, std::shared_ptr<Directory>& current_tree_node, std::shared_ptr<Directory> last_tree_node);

		Directory* Internal_FindDirectoryIterator(const std::filesystem::path& directory_path, const std::shared_ptr<Directory>& node) const;

		void CreateRoot(const std::filesystem::path& directory_path);


	private:
		std::shared_ptr<Directory> rootDirectory = nullptr;
	};
}