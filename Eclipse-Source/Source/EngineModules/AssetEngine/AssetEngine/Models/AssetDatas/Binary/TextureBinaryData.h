#pragma once

namespace Eclipse::Assets 
{
	struct TextureBinaryData
	{
		int width = -1;
		int height = -1;
		int channels = -1;

		size_t id = 0;
		std::vector<unsigned char> pixels;
	};
};