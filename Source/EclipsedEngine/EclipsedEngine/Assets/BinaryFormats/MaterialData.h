#pragma once

#include "AssetData.h"

#include "EclipsedEngine/Assets/Assets/Shader/VertexShaderAsset.h"
#include "EclipsedEngine/Assets/Assets/Shader/PixelShaderAsset.h"
#include "EclipsedEngine/Assets/Assets/TextureAsset.h"

#include "EclipsedEngine/Core/Math/Color.h"
#include "cereal/cereal.hpp"
#include "cereal/types/string.hpp"

#include <string>

namespace Eclipse::Assets
{
	struct SerializableMaterialData
	{
		std::string vertexShaderGuidStr;
		std::string pixelShaderGuidStr;
		std::string textureGuidStr;

		Math::Color color;

		template <class Archive>
		void serialize(Archive& ar, std::uint32_t const version)
		{
			ar(
				::cereal::make_nvp("vertex_shader", vertexShaderGuidStr),
				::cereal::make_nvp("pixel_shader", pixelShaderGuidStr),
				::cereal::make_nvp("texture", textureGuidStr),
				::cereal::make_nvp("color", color)
			);
		}
	};

	struct MaterialData : public AssetData {
		VertexShader vertexShader;
		PixelShader pixelShader;
		Texture texture;

		Math::Color color;

		unsigned int programID = 0;
	};
}

CEREAL_CLASS_VERSION(Eclipse::Assets::SerializableMaterialData, 0)