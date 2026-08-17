#pragma once

#include "EclipsedEngine/AssetManager/MetaData/Data/IAssetMeta.h"
#include <vector>

#include "cereal/cereal.hpp"
#include "cereal/types/String.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/polymorphic.hpp"

namespace Eclipse::Assets
{
	struct AudioMeta : public IAssetMeta
	{
		template <class Archive>
		void serialize(Archive& ar, const std::uint32_t version)
		{
			ar(cereal::base_class<IAssetMeta>(this));
		}
	};
}

CEREAL_REGISTER_TYPE(Eclipse::Assets::AudioMeta)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Eclipse::Assets::IAssetMeta, Eclipse::Assets::AudioMeta)
CEREAL_CLASS_VERSION(Eclipse::Assets::AudioMeta, 1)