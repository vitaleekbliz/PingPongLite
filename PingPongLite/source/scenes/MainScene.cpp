#include "MainScene.h"

MainScene::MainScene()
{
	isActive = true;
}

MainScene::~MainScene()
{
}

void MainScene::update()
{
	handlerCollisions();

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

	factory = std::make_unique<ObjectCreator>();

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

	bindDependencies();
}

bool MainScene::isRunning() const
{
	return isActive;
}

void MainScene::close()
{
	isActive = false;
}

void MainScene::bindDependencies()
{
	bindBallToComputer();
	resolvePaddleReferences();
}

void MainScene::bindBallToComputer()
{
	// Create reference for computer to follow the ball
	if (auto computerLock = computer)
	{
		if (auto compPtr = std::dynamic_pointer_cast<Computer>(computerLock))
		{
			compPtr->setBallReference(ball);
		}
	}
	else
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
					"Scene::setupInterfaces - Failed to lock Computer reference! The object may have been destroyed.");
	}
}

void MainScene::resolvePaddleReferences()
{
	// 1.Validate ball

	auto playerLock = player;
	if (!playerLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Player reference is expired.", __FUNCTION__);
		return;
	}

	auto playerObj = std::dynamic_pointer_cast<Player>(playerLock);
	if (!playerObj)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Failed to cast Object player to Player pointer.", __FUNCTION__);
		return;
	}

	// 2.Validate computer
	auto computerLock = computer;
	if (!computerLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Computer reference is expired.", __FUNCTION__);
		return;
	}

	auto computerObj = std::dynamic_pointer_cast<Computer>(computerLock);
	if (!computerObj)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Failed to cast Object computer to Computer pointer.",
					__FUNCTION__);
		return;
	}

	// 3. Validate ball
	auto ballLock = ball;
	if (!ballLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Ball reference is expired.", __FUNCTION__);
		return;
	}

	auto ballObj = std::dynamic_pointer_cast<Ball>(ballLock);
	if (!ballObj)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Failed to cast Object ball to Ball pointer.", __FUNCTION__);
		return;
	}

	// 4. Set dependencies
	ballObj->setComputerBoxCollider(computerObj->getBoxCollider());
	ballObj->setPlayerBoxCollider(playerObj->getBoxCollider());

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Successfully linked Paddles to Ball.");
}

void MainScene::handlerCollisions()
{
	auto ballLock = ball;
	if (!ballLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Ball reference is expired.", __FUNCTION__);
		return;
	}

	ballLock->getPosition();
	// TODO handle Colisions outside the ball class
}

std::shared_ptr<Object> MainScene::spawnObject(ObjectID object)
{
	std::shared_ptr<Object> newObject = factory->create(object);

	gameObjects.push_back(newObject);

	return newObject;
}

void MainScene::destroyObject(std::shared_ptr<Object> object)
{
	std::erase(gameObjects, object);
}
