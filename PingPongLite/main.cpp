#include "Creator.h"
#include "SDLHandler.h"
#include <vector>

int main()
{
	SDLHandler& sdlHandler = SDLHandler::get();

	sdlHandler.init();

	std::vector<Object> gameObjects;

	bool gameRunning = true;
	while (gameRunning)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i].update();
		}

		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i].render();
		}
	}

	sdlHandler.close();
	return 0;
}