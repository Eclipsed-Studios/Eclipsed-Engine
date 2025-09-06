#pragma once

#include <string>

namespace ENGINE_NAMESPACE
{
#define BASE_RESOURCE(type)									\
friend class AssetLoader;									\
friend class ResourceLoaderHelper;							\
public:														\
	type(const char* relativePath, const size_t& id) 		\
		: AbstractResource(relativePath, id) {  }			\
	type(const char* relativePath) 							\
		: AbstractResource(relativePath) {  }				\
	type() = default;										\
	~type() = default;										\
private:


	class AbstractResource
	{
	public:
		AbstractResource(const char* relativePath, const size_t& id);
		AbstractResource(const char* path);
		AbstractResource() = default;
		~AbstractResource() = default;

	public:
		const char* GetRelativePath() const;
		const size_t& GetID() const;

	private:
		std::string relativePath;
		size_t id;
	};
}