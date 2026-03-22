#include "core/SDLHandler.h"
#include "scenes/MainScene.h"

int main()
{
	SDLHandler& sdlHandler = SDLHandler::get();
	sdlHandler.init();

	MainScene mainScene = MainScene();
	mainScene.init();

	while (mainScene.isRunning())
	{
		sdlHandler.handleTickRate();

		if (!sdlHandler.handleEvents())
		{
			mainScene.close();
		}

		mainScene.update();

		mainScene.render();
	}

	sdlHandler.close();
	return 0;
}