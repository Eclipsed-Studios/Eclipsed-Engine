//#pragma once
//
//#include "EclipsedEngine/Assets/Importers/IAssetImporter.h"
//#include "OpenGL_Renderer.Core.hpp"
//
//namespace Eclipse::Graphics::OpenGL::Assets
//{
//	class OpenGL_TextureImporter final : public Eclipse::Assets::IAssetImporter
//	{
//    public:
//        Eclipse::Assets::ImportedData Import(const Eclipse::Assets::AssetMeta& meta) override;
//        Eclipse::Assets::ImportedData Import(const char* path) override;
//
//        Eclipse::Assets::AssetData* Process(const Eclipse::Assets::ImportedData& importedData) override;
//
//        void Serialize(const Eclipse::Assets::AssetData& data) override;
//
//        Eclipse::Assets::AssetData* Deserialize(const Eclipse::Assets::AssetMeta& assetMeta) override;
//        Eclipse::Assets::AssetData* Deserialize(const char* path) override;
//	};
//}