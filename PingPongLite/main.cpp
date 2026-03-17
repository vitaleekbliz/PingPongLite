#include "Creator.h"
#include "SDLHandler.h"
#include "Scene.h"

#include <vector>

int main()
{
	SDLHandler& sdlHandler = SDLHandler::get();
	sdlHandler.init();

	Scene mainScene = Scene();
	mainScene.init();

	Uint64 lastTick = SDL_GetTicks();

	while (mainScene.isRunning())
	{
		// TODO move handling to SDLhandler )))
		mainScene.handleEvents();

		// TODO write correct tick handling
		// start tick handling
		Uint64 nowTick = SDL_GetTicks();
		Uint64 difference = nowTick - lastTick;
		float deltaTime = 0;
		if (difference > 5)
		{
			deltaTime = (float)(nowTick - lastTick) / 1000.f;
			lastTick = nowTick;
		}

		// end tick handling

		mainScene.update(deltaTime);

		mainScene.render();
	}

	sdlHandler.close();
	return 0;
}