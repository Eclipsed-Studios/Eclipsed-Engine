#pragma once

#include <string>
#include "cereal/cereal.hpp"

namespace Eclipse
{
	struct AssetMetaSettings
	{
		std::string guid;

		template <class Archive>
		void serialize(Archive& ar)
		{
			ar(
				CEREAL_NVP(guid)
			);
		}
	};
}