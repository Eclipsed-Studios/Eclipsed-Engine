#include <AssetManagement/Loader/AssetLoader.hpp>

#include <filesystem>
#include <algorithm>

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <algorithm>
#include <string>

namespace ENGINE_NAMESPACE
{
	template<typename T>
	inline bool AssetLoader::IsExtensionSupported(const char* anExtension)
	{
		const std::vector<const char*>& supportedExtensions = supportedFileTypes.at(std::type_index(typeid(T)));

		auto it = std::find(supportedExtensions.begin(), supportedExtensions.end(), anExtension);
		
		return it != supportedExtensions.end();
	}
}




