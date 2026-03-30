#include "MainScene.h"

void MainScene::close()
{
	AudioHandler::get().close();
	TextureHandler::get().close();
	FontHandler::get().close();
	EffectHandler::get().close();
	isActive = false;
}

void MainScene::update()
{
	board->update();
	scoreBar->update();
	ball->update();
	paddleLeft->update();
	paddleRight->update();

	collisionDetector->update();
}

void MainScene::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	board->render();
	scoreBar->render();
	ball->render();
	paddleLeft->render();
	paddleRight->render();

	SDL_RenderPresent(renderer);
}

void MainScene::init()
{
	AudioHandler::get().init();
	TextureHandler::get().init();
	FontHandler::get().init();
	EffectHandler::get().init();

	ball = std::make_shared<Ball>();
	board = std::make_shared<Board>();
	scoreBar = std::make_shared<ScoreBar>();
	paddleLeft = std::make_shared<Paddle>();
	paddleRight = std::make_shared<Paddle>();

	collisionDetector = std::make_shared<CollisionDetection>();

	collisionDetector->addPaddles(paddleLeft, paddleRight);
	collisionDetector->setBallRef(ball);
	collisionDetector->addPaddleHitListener(ball);

	paddleLeft->setPosition({50, 400});
	paddleRight->setPosition({1230, 400});

	paddleLeft->setOriginalStrategy(PADDLE_STRATEGY::COMPUTER, ball);
	paddleRight->setOriginalStrategy(PADDLE_STRATEGY::PLAYER, ball);

	paddleLeft->addStrategyListener(scoreBar);

	board->setReference(ball);
	board->addBoundaryListener(scoreBar);
	board->addBoundaryListener(ball);

	isActive = true;
}
