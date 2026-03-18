#include "MainScene.h"

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

	// render gameObjects
	board->render();
	scoreBar->render();
	ball->render();
	computer->render();
	player->render();

	SDL_RenderPresent(renderer);
}

void MainScene::init()
{
	audioHandler = std::make_shared<AudioHandler>();
	audioHandler->init();
	textureHandler = std::make_shared<TextureHandler>();
	textureHandler->init();

	factory = std::make_shared<ObjectCreator>();

	// Populate using factory
	std::shared_ptr<Object> boardObject = factory->create(ObjectID::BOARD);
	std::shared_ptr<Object> computerObject = factory->create(ObjectID::COMPUTER);
	std::shared_ptr<Object> playerObject = factory->create(ObjectID::PLAYER);
	std::shared_ptr<Object> ballObject = factory->create(ObjectID::BALL);
	std::shared_ptr<Object> scoreBarObject = factory->create(ObjectID::SCORE_BAR);

	if (!boardObject || !computerObject || !playerObject || !ballObject || !scoreBarObject)
	{
		SDL_Log("Scene::init - Failed to create game Objects.");
		return;
	}

	// cast to original class and assign to Scene variables
	board = std::dynamic_pointer_cast<Board>(boardObject);
	computer = std::dynamic_pointer_cast<Computer>(computerObject);
	player = std::dynamic_pointer_cast<Player>(playerObject);
	ball = std::dynamic_pointer_cast<Ball>(ballObject);
	scoreBar = std::dynamic_pointer_cast<ScoreBar>(scoreBarObject);

	if (!board || !computer || !player || !ball || !scoreBar)
	{
		SDL_Log("Scene::init - Failed to cast Objects to their class.");
		return;
	}

	// BallObserver setup
	std::weak_ptr<BallSubscriber> audioHandlerSubscriber = std::dynamic_pointer_cast<BallSubscriber>(audioHandler);
	std::weak_ptr<BallSubscriber> scoreBarSubscriber = std::dynamic_pointer_cast<BallSubscriber>(scoreBarObject);
	std::weak_ptr<BallPublisher> ballPublisher = std::dynamic_pointer_cast<BallPublisher>(ball);

	if (!audioHandlerSubscriber.lock() || !scoreBarSubscriber.lock() || !ballPublisher.lock())
	{
		SDL_Log("Scene::init - Failed to setup BallObserver.");
		return;
	}

	ballPublisher.lock()->addListener(audioHandlerSubscriber.lock());
	ballPublisher.lock()->addListener(scoreBarSubscriber.lock());

	// Check colisions inside ball
	ball->setComputerReference(computer);
	ball->setPlayerReference(player);

	// follow ball movement
	computer->setBallReference(ball);

	isActive = true;
}

void MainScene::close()
{
	isActive = false;
}