#include "core/SDLHandler.h"
#include "scenes/Scene.h"

int main()
{

	SDLHandler& sdlHandler = SDLHandler::get();
	sdlHandler.init();

	Scene mainScene = Scene();
	mainScene.init();

	while (mainScene.isRunning())
	{
		if (!sdlHandler.handleEvents())
		{
			mainScene.close();
		}

		sdlHandler.handleTickRate();

		mainScene.update();

		mainScene.render();
	}

	sdlHandler.close();
	return 0;
}