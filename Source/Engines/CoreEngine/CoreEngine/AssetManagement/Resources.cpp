#include "Resources.h"

namespace Eclipse
{
	std::unordered_map<std::type_index, IResourceList*> Resources::myLoadedResources;
	AssetLoader Resources::myLoader;
}