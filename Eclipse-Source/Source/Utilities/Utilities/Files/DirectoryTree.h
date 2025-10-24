#pragma once

#include <filesystem>
#include "FileInfo.h"

namespace Eclipse::Utilities
{
	struct FileNode 
	{
		FileInfo info;
		std::vector<std::unique_ptr<FileNode>> children;
		bool isDirectory = false;
		bool isOpen = false;
	};

	class DirectoryTree final
	{
	public:
		DirectoryTree() = default;
		DirectoryTree(const std::filesystem::path& path);

	private:
		void Internal_SetupRoot(const std::filesystem::path& path);
		void Internal_BuildChildren(std::unique_ptr<FileNode>& node) const;

		FileNode* Internal_GetNode(const std::filesystem::path& path, std::unique_ptr<FileNode>& node);

	public:
		FileNode* GetRoot();     
		const FileNode* GetRoot() const;

		FileNode* GetNode(const std::filesystem::path& path);

	private:
		std::unique_ptr<FileNode> root = nullptr;
		std::filesystem::path relativePath;
	};
}