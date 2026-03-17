#include "Scene.h"

Scene::Scene()
{
	isActive = true;
}

Scene::~Scene()
{
}

void Scene::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void Scene::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}

	SDL_RenderPresent(renderer);
}

void Scene::init()
{
	populateScene();
	setupInterfaces();
}

bool Scene::isRunning() const
{
	return isActive;
}

void Scene::close()
{
	isActive = false;
}

void Scene::populateScene()
{
	// Order matters (moving objects below will result drawing board over all other objects) : rendering objects as a
	// list
	// TODO change update and render function to render in order
	board = spawnObject(ObjectID::BOARD);
	ball = spawnObject(ObjectID::BALL);
	computer = spawnObject(ObjectID::COMPUTER);
	player = spawnObject(ObjectID::PLAYER);
	scoreBar = spawnObject(ObjectID::SCORE_BAR);
}

void Scene::setupInterfaces()
{
	setupComputerToBallRef();
	setupBallListeners();
	setupBallListeners();
}

void Scene::setupComputerToBallRef()
{
	// Create reference for computer to follow the ball
	if (auto computerLock = computer.lock())
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

void Scene::setupBallListeners()
{
	// 1. Validate Ball
	auto ballLock = ball.lock();
	if (!ballLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] Ball reference is expired.", __FUNCTION__);
		return;
	}

	auto ballPub = std::dynamic_pointer_cast<BallPublisher>(ballLock);
	if (!ballPub)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] Ball exists but does not implement BallPublisher.",
					 __FUNCTION__);
		return;
	}

	// 2. Validate ScoreBar
	auto scoreBarLock = scoreBar.lock();
	if (!scoreBarLock)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] ScoreBar reference is expired.", __FUNCTION__);
		return;
	}

	auto scoreSub = std::dynamic_pointer_cast<BallSubscriber>(scoreBarLock);
	if (!scoreSub)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] ScoreBar exists but does not implement BallSubscriber.",
					 __FUNCTION__);
		return;
	}

	// 3. Final Wiring
	ballPub->addListener(scoreSub);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Successfully linked BallPublisher to ScoreBar (BallSubscriber).");
}

std::shared_ptr<Object> Scene::spawnObject(ObjectID object)
{
	std::shared_ptr<Object> newObject = factory->create(object);

	gameObjects.push_back(newObject);

	return newObject;
}

void Scene::destroyObject(std::shared_ptr<Object> object)
{
	std::erase(gameObjects, object);
}
