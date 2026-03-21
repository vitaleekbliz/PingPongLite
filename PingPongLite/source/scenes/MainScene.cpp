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
	ball->update();

	paddles[0]->update();
	paddles[1]->update();
}

void MainScene::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	board->render();
	scoreBar->render();
	ball->render();

	paddles[0]->render();
	paddles[1]->render();

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
	spawnObject(ObjectID::SCORE_BAR);

	spawnObject(ObjectID::PADDLE);
	spawnObject(ObjectID::PADDLE);

	paddles[0]->setPosition({50, 400});
	paddles[1]->setPosition({1230, 400});

	paddles[0]->setOriginalStrategy(PADDLE_STRATEGY::COMPUTER, ball->getPosition());
	paddles[1]->setOriginalStrategy(PADDLE_STRATEGY::PLAYER, ball->getPosition());

	scoreBar->setScoreDecoratorListeners(textureHandler, fontHandler);

	linkBallObserver(audioHandler, ball);
	linkBallObserver(scoreBar, ball);

	ball->setComputerReference(paddles[0]);
	ball->setPlayerReference(paddles[1]);

	isActive = true;
}

void MainScene::linkBallObserver(std::shared_ptr<BallSubscriber> subscriber, std::shared_ptr<BallPublisher> publisher)
{
	publisher->addBallListener(subscriber);
}

void MainScene::linkTextureObserver(std::shared_ptr<TextureSubscriber> subscriber,
									std::shared_ptr<TexturePublisher> publisher)
{
	publisher->addTextureListener(subscriber);
}

void MainScene::linkFontObserver(std::shared_ptr<FontSubscriber> subscriber, std::shared_ptr<FontPublisher> publisher)
{
	publisher->addFontListener(subscriber);
}

void MainScene::spawnObject(ObjectID id)
{
	std::shared_ptr<Object> newObj = factory->create(id);
	if (!newObj)
	{
		SDL_Log("Scene::populateScene - Failed to create game Objects.");
		return;
	}

	// Setup Object Observers
	linkTextureObserver(textureHandler, newObj);
	linkFontObserver(fontHandler, newObj);

	bool success = true;

	switch (id)
	{
	case ObjectID::BALL:
		ball = std::dynamic_pointer_cast<Ball>(newObj);
		if (!ball)
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
	case ObjectID::PADDLE:
		paddles.push_back(std::dynamic_pointer_cast<Paddle>(newObj));
		if (!paddles.back())
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
