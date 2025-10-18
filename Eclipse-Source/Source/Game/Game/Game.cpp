#include "Game.h"

#include "CoreEngine/Scenes/SceneManager.h"

namespace Eclipse
{
	void Game::Init()
	{
#ifdef _GAME
		SceneManager::LoadScene(0);
#endif 
	}
	}