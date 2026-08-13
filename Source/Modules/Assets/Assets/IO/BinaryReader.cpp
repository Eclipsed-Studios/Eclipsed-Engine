#include "BinaryReader.h"

#include "Core/PathManager.h"
#include <filesystem>

namespace Eclipse::Assets
{
	BinaryReader::BinaryReader(const std::string& path)
	{
		file = std::ifstream(path, std::ios::binary);
	}

	BinaryReader::BinaryReader(const GUID& guid)
	{
		std::filesystem::path path = PathManager::GetArtifactsPath();

		std::string guidStr = guid.ToString();
		path /= guidStr.substr(0, 2);
		path /= guidStr;

		file = std::ifstream(path, std::ios::binary);
	}

	bool BinaryReader::Open(const std::string& path)
	{
		file.open(path, std::ios::binary);

		return file.is_open();
	}

	void BinaryReader::Read(void* data, size_t size)
	{
		file.read(reinterpret_cast<char*>(data), size);
	}

	void BinaryReader::Close()
	{
		file.close();
	}

	bool BinaryReader::IsOpen() const
	{
		return file.is_open();
	}

	void BinaryReader::SetRead(size_t idx)
	{
		file.seekg(idx);
	}
}