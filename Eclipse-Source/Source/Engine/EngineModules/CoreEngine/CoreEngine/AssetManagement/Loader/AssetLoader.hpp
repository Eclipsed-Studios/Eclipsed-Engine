#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

#include "CoreEngine/AssetManagement/Resources.h"


#include <CoreEngine/AssetManagement/Resources/Texture.h>
#include <CoreEngine/AssetManagement/Resources/Shaders/PixelShader.h>
#include <CoreEngine/AssetManagement/Resources/Shaders/VertexShader.h>
#include <CoreEngine/AssetManagement/Resources/SpriteSheetAnimation.h>

#include "CoreEngine/AssetManagement/AssetExporter.h"

namespace Eclipse
{
	class Resources;
	class AssetLoader
	{
	public:
		void Init();
		std::unordered_map<size_t, FileEntryData> loadedDatas;


		template <typename T>
		void LoadFromPath(const char* aPath, T& outResource) {  }

		template <typename T>
		void LoadAll(std::vector<T>& outResources) { __noop; }

		template<typename T>
		void Unload() {};

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