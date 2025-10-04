#include "DirectoryTree.h"

namespace Eclipse::Utilities
{
	namespace fs = std::filesystem;


	DirectoryTree::DirectoryTree(const fs::path& iteration_path)
	{
		CreateRoot(iteration_path);
		Internal_IterateItems(iteration_path, rootDirectory, nullptr);
	}

	const Directory* DirectoryTree::GetRoot() const { return rootDirectory.get(); }
	Directory* DirectoryTree::GetRoot() { return rootDirectory.get(); }

	const Directory* DirectoryTree::GetDirectoryFromPath(const fs::path& directory_path) const
	{
		return Internal_FindDirectoryIterator(directory_path, rootDirectory);
	}

	Directory* DirectoryTree::GetDirectoryFromPath(const fs::path& directory_path)
	{
		return Internal_FindDirectoryIterator(directory_path, rootDirectory);
	}

	const FileInfo& DirectoryTree::GetRootPath() const
	{
		return rootDirectory->path;
	}

	void DirectoryTree::Internal_IterateItems(const fs::path& start_path, std::shared_ptr<Directory>& current_tree_node, std::shared_ptr<Directory> last_tree_node)
	{
		current_tree_node->path = FileInfo::GetFileInfo(start_path);
		current_tree_node->path.relativeFilePath = fs::relative(start_path, SOURCE_PATH).lexically_normal();


		for (const fs::directory_entry& entry : fs::directory_iterator(start_path))
		{
			FileInfo info = FileInfo::GetFileInfo(entry);
			info.relativeFilePath = fs::relative(entry.path(), ASSET_PATH).lexically_normal();

			if (info.type == FileInfo::FileType_Directory)
			{
				current_tree_node->subDirectories.emplace_back(std::make_shared<Directory>());
				Internal_IterateItems(entry, current_tree_node->subDirectories.back(), current_tree_node);
			}
			else
			{
				current_tree_node->files.emplace_back(info);
			}
		}

	}

	Directory* DirectoryTree::Internal_FindDirectoryIterator(const fs::path& directory_path, const std::shared_ptr<Directory>& node) const
	{
		if (!node) return nullptr;

		auto normalize = [](const fs::path& p) -> std::string {
			return p.lexically_normal().generic_string() + "/";
			};

		std::string target = normalize(directory_path);

		if (fs::equivalent(node->path.filePath, target)) 
		{
			return node.get();
		}

		for (const auto& dir : node->subDirectories) 
		{
			Directory* found = Internal_FindDirectoryIterator(directory_path, dir);
			if (found) return found;
		}

		return nullptr;
	}

	void DirectoryTree::CreateRoot(const std::filesystem::path& directory_path)
	{
		rootDirectory = std::make_shared<Directory>();
		rootDirectory->path = FileInfo::GetFileInfo(directory_path);
	}
}
