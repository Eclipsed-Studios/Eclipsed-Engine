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

	struct SimonsRövhål : public AssetMetaSettings
	{
		int age;

		template <class Archive>
		void serialize(Archive& ar)
		{
			AssetMetaSettings::serialize(ar);

			ar(
				CEREAL_NVP(age)
			)
		}
	};

}