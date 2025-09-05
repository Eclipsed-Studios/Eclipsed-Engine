#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>



#include <AssetManagement/Resources/Texture.h>

namespace ENGINE_NAMESPACE
{
	class AssetLoader
	{
	public:
		template <typename T>
		void LoadFromPath(const char* aPath, T& outResource) { throw std::runtime_error("OWADDAWADW"); }

		template <typename T>
		void LoadAll(std::vector<T>& outResources) { __noop; }

		template <typename T>
		bool IsExtensionSupported(const char* anExtension);


		// MOve to helper class
		unsigned char* Load_Texture_STB(const char* aPath, Texture& outResource);
		void FreeData_STB(unsigned char* someData);

	private:
		const std::unordered_map<std::type_index, std::vector<const char*>> supportedFileTypes =
		{
			{ typeid(Texture), {".png"} }
		};
	};
}

#include "AssetLoader.inl"
#include "TypeLoaders/TextureLoader.inl"
#include "TypeLoaders/ShaderLoader.inl"
#include "TypeLoaders/SpriteAnimationLoader.inl"