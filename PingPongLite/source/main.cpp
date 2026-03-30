#include "core/SDLHandler.h"
#include "scenes/MainScene.h"
#include <Windows.h>

int main()
{
#ifndef _DEBUG
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

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