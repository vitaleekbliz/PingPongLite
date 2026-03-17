#include "Scene.h"

Scene::Scene()
{
	folderPath = "assets\\arts\\";
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
	// Order matters: rendering objects as a list
	// TODO change update and render function to render in order

	// Populate Scene
	auto board = createObject(ObjectID::BOARD, "Board.png", folderPath, 1280, 680);
	auto ball = createObject(ObjectID::BALL, "Ball.png", folderPath, 30, 30);
	auto computer = createObject(ObjectID::COMPUTER, "Computer.png", folderPath, 17, 120);
	auto player = createObject(ObjectID::PLAYER, "Player.png", folderPath, 17, 120);
	auto scoreBar = createObject(ObjectID::SCORE_BAR, "ScoreBar.png", folderPath, 600, 40);

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

bool Scene::isRunning() const
{
	return isActive;
}

void Scene::close()
{
	isActive = false;
}

std::shared_ptr<Object> Scene::createObject(ObjectID object, std::string fileName, std::string& folderPath, int w,
											int h)
{
	auto newObject = factory->create(object);
	newObject->setMetaData(fileName, folderPath, w, h);
	newObject->loadMedia();
	gameObjects.push_back(newObject);
	return newObject;
}
