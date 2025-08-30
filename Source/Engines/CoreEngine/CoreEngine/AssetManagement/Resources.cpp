#include "Resources.h"

namespace ENGINE_NAMESPACE
{
	std::unordered_map<std::type_index, IResourceList*> Resources::myLoadedResources;
	AssetLoader Resources::myLoader;
}