//#include "AssetCooker.h"
//
//#include <variant>
//
//namespace Eclipse::Assets
//{
//	template<>
//	inline CookedAsset AssetCooker::Cook(const TextureData& data)
//	{
//		size_t headerSize = sizeof(int) // Width
//			+ sizeof(int)				// Height
//			+ sizeof(int)				// Channels
//			+ sizeof(size_t);
//
//		size_t pixelSize = data.width * data.height * data.channels;
//
//		size_t totalSize = headerSize + pixelSize;
//
//		CookedAsset cookedAsset;
//
//		cookedAsset.data = new char[totalSize];
//		cookedAsset.size = totalSize;
//
//		char* ptr = cookedAsset.data;
//
//		memcpy(ptr, &data.id, sizeof(size_t)); ptr += sizeof(size_t);
//
//		memcpy(ptr, &data.width, sizeof(int)); ptr += sizeof(int);
//		memcpy(ptr, &data.height, sizeof(int)); ptr += sizeof(int);
//		memcpy(ptr, &data.channels, sizeof(int)); ptr += sizeof(int);
//
//		memcpy(ptr, data.pixels, pixelSize);
//
//		return cookedAsset;
//	}
//}