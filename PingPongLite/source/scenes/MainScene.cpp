#include "MainScene.h"

void MainScene::close()
{
	AudioHandler::get().close();
	TextureHandler::get().close();
	FontHandler::get().close();
	EffectHandler::get().close();
	isActive = false;
}

void MainScene::run()
{
	init();

	SDLHandler::get().resetTicks();

	// its infinite scene no exits so far
	while (isActive)
	{
		SDLHandler::get().handleTickRate();

		SDLHandler::get().handleEvents();

		update();

		render();
	}

	close();
}

void MainScene::update()
{
	board->update();
	scoreBar->update();
	ball->update();
	paddleLeft->update();
	paddleRight->update();

	collisionDetector->update();
	collectibleSpawner->update();
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

	collectibleSpawner->render();

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

	collisionDetector = std::make_shared<CollisionDetector>();
	collectibleSpawner = std::make_shared<CollectibleSpawner>();
	collectibleSpawner->setPosition({1280 / 2, 720 / 2});

	collisionDetector->addPaddles(paddleLeft, paddleRight);
	collisionDetector->setBallRef(ball);
	collisionDetector->addPaddleHitListener(ball);
	collisionDetector->addCollectiblePickedListener(collectibleSpawner);

	collectibleSpawner->addCollectibleSpawnListener(collisionDetector);
	collectibleSpawner->addChangeScoreListener(scoreBar);
	collectibleSpawner->addStrategyListener(paddleLeft);
	collectibleSpawner->addStrategyListener(paddleRight);
	collectibleSpawner->addStrategyListener(scoreBar);

	paddleLeft->setPosition({50, 400});
	paddleRight->setPosition({1230, 400});

	paddleLeft->setOriginalStrategy(PADDLE_STRATEGY::COMPUTER, ball);
	paddleRight->setOriginalStrategy(PADDLE_STRATEGY::PLAYER, ball);

	board->setReference(ball);
	board->addBoundaryListener(scoreBar);
	board->addBoundaryListener(ball);

	isActive = true;
}
