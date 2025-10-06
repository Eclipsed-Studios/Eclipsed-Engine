#include "Game.h"

#include "Scenes/SceneManager.h"

namespace Eclipse
{
	void Game::Init()
	{
#ifdef _GAME
		SceneManager::LoadScene(0);
#endif 
	}
	}