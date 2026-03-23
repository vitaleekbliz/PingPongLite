#include "MainScene.h"

MainScene::~MainScene()
{
	close();
}

void MainScene::close()
{
	AudioHandler::get().close();
	TextureHandler::get().close();
	FontHandler::get().close();
	isActive = false;
}

void MainScene::update()
{
	board->update();
	scoreBar->update();
	ball->update();
	computer->update();
	player->update();
}

void MainScene::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	board->render();
	scoreBar->render();
	ball->render();
	computer->render();
	player->render();

	SDL_RenderPresent(renderer);
}

void MainScene::init()
{
	AudioHandler::get().init();
	TextureHandler::get().init();
	FontHandler::get().init();

	ball = std::make_shared<Ball>();
	board = std::make_shared<Board>();
	scoreBar = std::make_shared<ScoreBar>();
	computer = std::make_shared<Paddle>();
	player = std::make_shared<Paddle>();

	computer->setPosition({50, 400});
	player->setPosition({1230, 400});

	computer->setOriginalStrategy(PADDLE_STRATEGY::COMPUTER, ball);
	player->setOriginalStrategy(PADDLE_STRATEGY::PLAYER, ball);

	computer->addStrategyListener(scoreBar);
	ball->setPaddleReferences(player, computer);

	board->setReference(ball);
	board->addBoundaryListener(scoreBar);
	board->addBoundaryListener(ball);

	isActive = true;
}
