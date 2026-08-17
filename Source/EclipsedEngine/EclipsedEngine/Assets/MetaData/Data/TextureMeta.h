#pragma once

#include "EclipsedEngine/Assets/MetaData/Data/IAssetMeta.h"
#include <vector>

#include "cereal/cereal.hpp"
#include "cereal/types/String.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/polymorphic.hpp"

#include "Core/Math/RectSizePos.h"

namespace Eclipse::Assets
{
	struct Rect {
		Math::RectSizePos rect;
		std::string name;

		template <class Archive>
		void serialize(Archive& ar, const std::uint32_t version)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(rect));
		}
	};

	struct TextureMeta : public IAssetMeta
	{
		std::vector<Rect> spriteRects;

		template <class Archive>
		void serialize(Archive& ar, const std::uint32_t version)
		{
			ar(cereal::base_class<IAssetMeta>(this));
			ar(CEREAL_NVP(spriteRects));
		}
	};
}

CEREAL_REGISTER_TYPE(Eclipse::Assets::TextureMeta)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Eclipse::Assets::IAssetMeta, Eclipse::Assets::TextureMeta)
CEREAL_CLASS_VERSION(Eclipse::Assets::TextureMeta, 2)