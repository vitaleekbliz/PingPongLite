#pragma once
#include "core/SDLHandler.h"
#include "scenes/IntroScene.h"
#include "scenes/MainScene.h"

namespace Game
{
void run()
{
	SDLHandler::get().init();

	// play intro
	std::shared_ptr<Scene> activeScene = std::make_shared<IntroScene>();
	activeScene->run();

	// final (infinite) scene
	activeScene = std::make_shared<MainScene>();
	activeScene->run();

	SDLHandler::get().close();
}
} // namespace Game