#include "BinaryWriter.h"

#include "CoreEngine/PathManager.h"
#include <filesystem>

namespace Eclipse::Assets
{
	BinaryWriter::BinaryWriter(const std::string& Path)
	{
		path = Path;
		file = std::ofstream(Path, std::ios::binary);
	}

	BinaryWriter::BinaryWriter(const GUID& guid)
	{
		std::filesystem::path path = PathManager::GetArtifactsPath();

		std::string guidStr = guid.ToString();
		path /= guidStr.substr(0, 2);
		path /= guidStr;

		this->path = path;

		CreateFile(path.generic_string());
		file = std::ofstream(path, std::ios::binary);
	}

	bool BinaryWriter::Open(const std::string& Path)
	{
		path = Path;
		file = std::ofstream(Path, std::ios::binary);
		return file.is_open();
	}

	void BinaryWriter::Write(const void* data, size_t size)
	{
		file.write(reinterpret_cast<const char*>(data), size);
	}

	void BinaryWriter::Close()
	{
		file.close();
	}

	bool BinaryWriter::IsOpen() const
	{
		return file.is_open();
	}

	std::filesystem::path BinaryWriter::GetPath() const
	{
		return path;
	}

	void BinaryWriter::CreateFile(const std::string& path)
	{
		std::filesystem::create_directories(std::filesystem::path(path).parent_path());
		std::ofstream file(path);
		file.close();
	}
}