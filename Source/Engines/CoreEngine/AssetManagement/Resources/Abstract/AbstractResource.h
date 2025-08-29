#pragma once

#include <string>

namespace ENGINE_NAMESPACE
{
#define BASE_RESOURCE(type)									\
friend class AssetLoader;									\
public:														\
	type(const char* relativePath, const size_t& id) 		\
		: AbstractResource(relativePath, id) { __noop; }	\
	type() = default;										\
	~type() = default;										\
private:


	class AbstractResource
	{
	public:
		AbstractResource(const char* relativePath, const size_t& id);
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