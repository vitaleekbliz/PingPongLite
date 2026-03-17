#include "Scene.h"

Scene::Scene()
{
	folderPath = "assets\\arts\\";
	isActive = true;
}

Scene::~Scene()
{
}

void Scene::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			isActive = false;
			break;
		}
	}
}

void Scene::update(float deltaTime)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(deltaTime);
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
	// Order matter rendering object as a list
	auto board = createObject(ObjectID::BOARD, "Board.png", folderPath, 1280, 680);
	auto ball = createObject(ObjectID::BALL, "Ball.png", folderPath, 30, 30);
	auto computer = createObject(ObjectID::COMPUTER, "Computer.png", folderPath, 17, 120);

	// Create reference for computer to follow the ball
	if (auto sharedObj = computer.lock())
	{
		auto compPtr = std::dynamic_pointer_cast<Computer>(sharedObj);

		if (compPtr)
		{
			compPtr->setBallReference(ball);
		}
	}

	auto player = createObject(ObjectID::PLAYER, "Player.png", folderPath, 17, 120);
	auto scoreBar = createObject(ObjectID::SCORE_BAR, "ScoreBar.png", folderPath, 600, 40);
}

bool Scene::isRunning()
{
	return isActive;
}

std::weak_ptr<Object> Scene::createObject(ObjectID object, std::string fileName, std::string& folderPath, int w, int h)
{
	auto newObject = factory->create(object);
	newObject->setMetaData(fileName, folderPath, w, h);
	newObject->loadMedia();
	gameObjects.push_back(newObject);
	return newObject;
}
