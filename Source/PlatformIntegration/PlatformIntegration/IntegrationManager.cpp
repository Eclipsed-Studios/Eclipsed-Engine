#include "IntegrationManager.h"

#include "DiscordIntegration.h"

namespace ENGINE_NAMESPACE::PlatformIntegration
{
	void IntegrationManager::Update()
	{
		Discord::Update();
	}
}