#include "DirectoryTree.h"

namespace Eclipse::Utilities
{
	namespace fs = std::filesystem;

	DirectoryTree::DirectoryTree(const std::filesystem::path& path) : relativePath(path)
	{
		Internal_SetupRoot(path);
		Internal_BuildChildren(root);
	}

	void DirectoryTree::Internal_SetupRoot(const std::filesystem::path& path)
	{
		root = std::make_unique<FileNode>();
		root->info = Utilities::FileInfo::GetFileInfo(path);
		root->isDirectory = root->info.type == Utilities::FileInfo::FileStatus_Directory;
	}

	void DirectoryTree::Internal_BuildChildren(std::unique_ptr<FileNode>& node) const
	{
		namespace fs = std::filesystem;

		for (const fs::directory_entry& entry : fs::directory_iterator(node->info.filePath))
		{
			std::unique_ptr<FileNode> child = std::make_unique<FileNode>();
			child->info = Utilities::FileInfo::GetFileInfo(entry);
			child->info.SetRelativePath(relativePath);

			if (entry.is_directory())
			{
				child->isDirectory = true;
			}


			if (child->isDirectory)
			{
				Internal_BuildChildren(child);
			}

			node->children.push_back(std::move(child));
		}

		std::sort(node->children.begin(), node->children.end(),
			[](const std::unique_ptr<FileNode>& a, const std::unique_ptr<FileNode>& b)
			{
				if (a->isDirectory != b->isDirectory)
					return a->isDirectory > b->isDirectory;

				if (a->info.type != b->info.type)
					return a->info.type > b->info.type;

				return a->info.filePath.filename() < b->info.filePath.filename();
			});
	}

	FileNode* DirectoryTree::Internal_GetNode(const std::filesystem::path& path, std::unique_ptr<FileNode>& node)
	{
		if (std::filesystem::equivalent(node->info.filePath, path))
			return node.get();

		for (auto& child : node->children)
		{
			if (auto result = Internal_GetNode(path, child))
				return result;
		}

		return nullptr;
	}

	FileNode* DirectoryTree::GetRoot()
	{
		return root.get();
	}
	
	const FileNode* DirectoryTree::GetRoot() const
	{
		return root.get();
	}

	FileNode* DirectoryTree::GetNode(const std::filesystem::path& path)
	{
		return Internal_GetNode(path, root);
	}
}
