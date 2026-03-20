#include "MainScene.h"

MainScene::~MainScene()
{
	close();
}

void MainScene::close()
{
	audioHandler->close();
	textureHandler->close();
	isActive = false;
}

void MainScene::update()
{
	board->update();
	scoreBar->update();
	computer->update();
	player->update();
	ball->update();
}

void MainScene::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// render gameObjects
	board->render();
	scoreBar->render();
	computer->render();
	player->render();
	ball->render();

	SDL_RenderPresent(renderer);
}

void MainScene::init()
{
	audioHandler = std::make_shared<AudioHandler>();
	audioHandler->init();

	textureHandler = std::make_shared<TextureHandler>();
	textureHandler->init();

	fontHandler = std::make_shared<FontHandler>();

	factory = std::make_unique<ObjectCreator>();

	spawnObject(ObjectID::BALL);
	spawnObject(ObjectID::BOARD);
	spawnObject(ObjectID::COMPUTER);
	spawnObject(ObjectID::PLAYER);
	spawnObject(ObjectID::SCORE_BAR);

	linkBallObserver(audioHandler, ball);
	linkBallObserver(scoreBar, ball);

	linkTextureObserver(textureHandler, ball);
	linkTextureObserver(textureHandler, board);
	linkTextureObserver(textureHandler, scoreBar);
	linkTextureObserver(textureHandler, player);
	linkTextureObserver(textureHandler, computer);

	linkFontObserver(fontHandler, ball);
	linkFontObserver(fontHandler, board);
	linkFontObserver(fontHandler, scoreBar);
	linkFontObserver(fontHandler, player);
	linkFontObserver(fontHandler, computer);

	// Check colisions inside ball
	ball->setComputerReference(computer);
	ball->setPlayerReference(player);

	// follow ball movement
	computer->setBallReference(ball);

	isActive = true;
}

void MainScene::linkBallObserver(std::shared_ptr<BallSubscriber> subscriber, std::shared_ptr<BallPublisher> publisher)
{
	publisher->addListener(subscriber);
}

void MainScene::linkTextureObserver(std::shared_ptr<TextureSubscriber> subscriber,
									std::shared_ptr<TexturePublisher> publisher)
{
	publisher->addListener(subscriber);
}

void MainScene::linkFontObserver(std::shared_ptr<FontSubscriber> subscriber, std::shared_ptr<FontPublisher> publisher)
{
	publisher->addListener(subscriber);
}

void MainScene::spawnObject(ObjectID id)
{
	std::shared_ptr<Object> newObj = factory->create(id);
	if (!newObj)
	{
		SDL_Log("Scene::populateScene - Failed to create game Objects.");
		return;
	}

	bool success = true;

	switch (id)
	{
	case ObjectID::BALL:
		ball = std::dynamic_pointer_cast<Ball>(newObj);
		if (!ball)
			success = false;
		break;
	case ObjectID::COMPUTER:
		computer = std::dynamic_pointer_cast<Computer>(newObj);
		if (!computer)
			success = false;
		break;
	case ObjectID::PLAYER:
		player = std::dynamic_pointer_cast<Player>(newObj);
		if (!player)
			success = false;
		break;
	case ObjectID::SCORE_BAR:
		scoreBar = std::dynamic_pointer_cast<ScoreBar>(newObj);
		if (!scoreBar)
			success = false;
		break;
	case ObjectID::BOARD:
		board = std::dynamic_pointer_cast<Board>(newObj);
		if (!board)
			success = false;
		break;
	default:
		break;
	}

	if (!success)
	{
		SDL_Log("Scene::populateScene - Failed to cast Objects to their class.");
		return;
	}
}
