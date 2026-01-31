#include "PrefabLoader.h"
#include "AssetEngine/AssetRegistry.h"
#include "fmod/fmod.h"
#include "fmod/fmod.hpp"

#include "CoreEngine/MainSingleton.h"

#include <fstream>


namespace Eclipse::Assets
{
	PrefabHandle* PrefabLoader::Load(const size_t& id)
	{
		PrefabHandle* handle = new PrefabHandle;

		Load(id, handle);
		return handle;
	}
	void PrefabLoader::Load(const size_t& id, PrefabHandle* handle)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);
		handle->assetID = id;

		std::ifstream stream(entry.path);
		if (!stream.is_open()) {
			return;
		}

		size_t prefSize = std::filesystem::file_size(entry.path);

		handle->data = reinterpret_cast<char*>(malloc(prefSize + 1));
		stream.read(handle->data, prefSize);
		memset(handle->data + prefSize, '\0', 1);
		stream.close();
	}
}
