#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/Texture.h>

#include <glad/glad.h>



namespace ENGINE_NAMESPACE
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, Texture& outResource)
	{

	}
}