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

	std::shared_ptr<Scene> activeScene = std::make_shared<MainScene>();
	activeScene->init();

	while (activeScene->isRunning())
	{
		sdlHandler.handleTickRate();

		if (!sdlHandler.handleEvents())
		{
			return 0;
		}

		activeScene->update();

		activeScene->render();
	}

	sdlHandler.close();
	return 0;
}