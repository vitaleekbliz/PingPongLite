#include "IntroScene.h"

void IntroScene::run()
{
	init();

	SDLHandler::get().resetTicks();
	while (isActive)
	{
		SDLHandler::get().handleTickRate();

		SDLHandler::get().handleEvents();

		update();

		render();
	}

	close();
}

void IntroScene::update()
{
	float deltaTime = SDLHandler::get().getTick();
	sceneLifetime -= deltaTime;
	if (sceneLifetime < 0.f)
	{
		isActive = false;
	}
}

void IntroScene::render()
{
	// clear screen
	SDL_SetRenderDrawColor(SDLHandler::get().getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDLHandler::get().getRenderer());

	board->render();

	computer->render();
	player->render();

	potion->render();
	redStar->render();
	blueStar->render();

	renderCooldown();
	renderNotes();

	// draw
	SDL_RenderPresent(SDLHandler::get().getRenderer());
}

void IntroScene::init()
{
	TextureHandler::get().init();

	computer = std::make_shared<Paddle>();
	player = std::make_shared<Paddle>();
	board = std::make_shared<Board>();
	potion = std::make_shared<Potion>();
	redStar = std::make_shared<RedStar>();
	blueStar = std::make_shared<BlueStar>();

	board->setPosition(objectPositions.board);
	board->setSize(boardSize);

	computer->setPosition(objectPositions.computer);
	player->setPosition(objectPositions.player);
	potion->setPosition(objectPositions.potion);
	redStar->setPosition(objectPositions.redStar);
	blueStar->setPosition(objectPositions.blueStar);

	player->setOriginalStrategy(PADDLE_STRATEGY::PLAYER, player);
}
void IntroScene::close()
{
	TextureHandler::get().close();
}

void IntroScene::renderCooldown()
{
	std::string current_time = "Intro time left : " + std::to_string((int)std::ceil(sceneLifetime));
	FontHandler::get().drawText(FONT::CALIBRI, current_time.c_str(), &objectPositions.textCooldown, 32, colors.grey);
}

void IntroScene::renderNotes()
{
	FontHandler::get().drawText(FONT::CALIBRI, notes.posion, &objectPositions.textPosion, 32, colors.grey);
	FontHandler::get().drawText(FONT::CALIBRI, notes.redStar, &objectPositions.textRedStar, 32, colors.orange);
	FontHandler::get().drawText(FONT::CALIBRI, notes.blueStar, &objectPositions.textBlueStar, 32, colors.blue);
	FontHandler::get().drawText(FONT::CALIBRI, notes.computer, &objectPositions.textComputer, 32, colors.blue);
	FontHandler::get().drawText(FONT::CALIBRI, notes.player, &objectPositions.textPlayer, 32, colors.orange);
}
