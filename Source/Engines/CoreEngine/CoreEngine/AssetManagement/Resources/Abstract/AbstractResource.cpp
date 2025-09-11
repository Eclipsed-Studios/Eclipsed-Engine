#include "AbstractResource.h"

#include <filesystem>

namespace Eclipse
{
	AbstractResource::AbstractResource(const char* _relativePath, const size_t& _id)
		: relativePath(_relativePath), id(_id) { }

	AbstractResource::AbstractResource(const char* path) 
	{
		relativePath = std::filesystem::relative(path, ASSET_PATH).string();
		id = std::hash<std::string>{}(relativePath);
	}

	const char* AbstractResource::GetRelativePath() const
	{
		return relativePath.c_str();
	}

	const size_t& AbstractResource::GetID() const
	{
		return id;
	}
}