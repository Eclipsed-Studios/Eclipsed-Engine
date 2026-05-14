#pragma once

#include "IAssetMeta.h"
#include <vector>

#include "cereal/cereal.hpp"
#include "cereal/types/String.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/polymorphic.hpp"

namespace Eclipse::Assets
{
	enum class AudioFlags : int
	{
		None = 0,
		Audio3D = 1 << 0,
		Stream = 1 << 1,
		Decompress = 1 << 2,
		KeepCompressed = 1 << 3,
		Preload = 1 << 4,
		AsyncLoad = 1 << 5,
	};

	struct AudioMeta : public IAssetMeta
	{
		int flags = (int)AudioFlags::None;

		template <class Archive>
		void serialize(Archive& ar, const std::uint32_t version)
		{
			ar(cereal::base_class<IAssetMeta>(this));
			ar(CEREAL_NVP(flags));
		}
	};
}

CEREAL_REGISTER_TYPE(Eclipse::Assets::AudioMeta)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Eclipse::Assets::IAssetMeta, Eclipse::Assets::AudioMeta)
CEREAL_CLASS_VERSION(Eclipse::Assets::AudioMeta, 1)