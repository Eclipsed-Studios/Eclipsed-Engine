#pragma once

namespace Eclipse
{
	struct CookedAsset 
	{
		size_t id;
		std::vector<char> data;
		size_t size;
	};
}