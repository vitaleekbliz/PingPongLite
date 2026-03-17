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
		mainScene.handleEvents();

		Uint64 nowTick = SDL_GetTicks();
		float deltaTime = (float)(nowTick - lastTick) / 1000.f;
		lastTick = nowTick;

		mainScene.update(deltaTime);

		mainScene.render();
	}

	sdlHandler.close();
	return 0;
}