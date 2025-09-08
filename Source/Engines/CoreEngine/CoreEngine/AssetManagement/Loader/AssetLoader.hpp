#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>



#include <AssetManagement/Resources/Texture.h>
#include <AssetManagement/Resources/Shaders/PixelShader.h>
#include <AssetManagement/Resources/Shaders/VertexShader.h>
#include <AssetManagement/Resources/SpriteSheetAnimation.h>

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

	private:
		const std::unordered_map<std::type_index, std::vector<const char*>> supportedFileTypes =
		{
			{ typeid(Texture), {".png", ".jpg", ".jpeg",".bmp", ".tga", ".gif", ".psd", ".hdr" }},
			{ typeid(PixelShader), { ".glsl" }},
			{ typeid(VertexShader), { ".glsl" }},
			{ typeid(SpriteSheetAnimation), { ".spriteanim" }},
		};
	};
}

#include "AssetLoader.inl"
#include "TypeLoaders/TextureLoader.inl"
#include "TypeLoaders/ShaderLoader.inl"
#include "TypeLoaders/SpriteAnimationLoader.inl"
#include "TypeLoaders/AudioLoader.inl"