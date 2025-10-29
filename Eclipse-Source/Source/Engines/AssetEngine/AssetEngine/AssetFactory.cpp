#include "AssetFactory.h"

#include <fstream>

#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"

namespace Eclipse::Assets
{
	void AssetFactory::CreateMaterial(const char* path)
	{
		std::ofstream out(path, std::ios::binary);

		size_t id = 0;
		Math::Color color = { 1.f ,1.f, 1.f, 1.f };
		out.write(reinterpret_cast<const char*>(&id), sizeof(size_t)); // Texture id
		out.write(reinterpret_cast<const char*>(&id), sizeof(size_t)); // ps
		out.write(reinterpret_cast<const char*>(&id), sizeof(size_t)); // vs
		out.write(reinterpret_cast<const char*>(&color), sizeof(Math::Color)); // color
		out.close();
	}
}