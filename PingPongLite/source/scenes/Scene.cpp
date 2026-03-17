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
	// Create reference for computer to follow the ball
	if (auto compPtr = std::dynamic_pointer_cast<Computer>(computer))
	{
		compPtr->setBallReference(ball);
	}

	// Subscribe Score to BallPublisher
	if (auto ballPub = std::dynamic_pointer_cast<BallPublisher>(ball))
	{
		if (auto scoreSub = std::dynamic_pointer_cast<BallSubscriber>(scoreBar))
		{
			ballPub->addListener(scoreSub);
		}
	}
}

std::shared_ptr<Object> Scene::spawnObject(ObjectID object)
{
	std::shared_ptr<Object> newObject = factory->create(object);

	gameObjects.push_back(newObject);

	return newObject;
}
