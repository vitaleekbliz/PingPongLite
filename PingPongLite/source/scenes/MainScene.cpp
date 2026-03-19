#include "MainScene.h"

MainScene::~MainScene()
{
	close();
}

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

	factory = std::make_unique<ObjectCreator>();

	populateScene(ObjectID::BALL);
	populateScene(ObjectID::BOARD);
	populateScene(ObjectID::COMPUTER);
	populateScene(ObjectID::PLAYER);
	populateScene(ObjectID::SCORE_BAR);

	setupBallObserver();

	setupTextureObserver();

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

void MainScene::populateScene(ObjectID id)
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

void MainScene::setupBallObserver()
{
	std::weak_ptr<BallSubscriber> audioHandlerSubscriber = std::dynamic_pointer_cast<BallSubscriber>(audioHandler);
	std::weak_ptr<BallSubscriber> scoreBarSubscriber = std::dynamic_pointer_cast<BallSubscriber>(scoreBar);
	std::weak_ptr<BallPublisher> ballPublisher = std::dynamic_pointer_cast<BallPublisher>(ball);

	if (!audioHandlerSubscriber.lock() || !scoreBarSubscriber.lock() || !ballPublisher.lock())
	{
		SDL_Log("Scene::setupBallObserver - Failed to setup BallObserver.");
		return;
	}

	ballPublisher.lock()->addListener(audioHandlerSubscriber.lock());
	ballPublisher.lock()->addListener(scoreBarSubscriber.lock());
}

void MainScene::setupTextureObserver()
{
	std::shared_ptr<TextureSubscriber> textureSubscriber = std::dynamic_pointer_cast<TextureSubscriber>(textureHandler);
	if (!textureSubscriber)
	{
		SDL_Log("Scene::setupTextureObserver - Failed to cast texture handler to texture subscriber.");
		return;
	}

	std::shared_ptr<TexturePublisher> ballPublisher = std::dynamic_pointer_cast<TexturePublisher>(ball);
	std::shared_ptr<TexturePublisher> boardPublisher = std::dynamic_pointer_cast<TexturePublisher>(board);
	std::shared_ptr<TexturePublisher> computerPublisher = std::dynamic_pointer_cast<TexturePublisher>(computer);
	std::shared_ptr<TexturePublisher> playerPublisher = std::dynamic_pointer_cast<TexturePublisher>(player);
	std::shared_ptr<TexturePublisher> scoreBarPublisher = std::dynamic_pointer_cast<TexturePublisher>(scoreBar);
	if (!boardPublisher || !computerPublisher || !playerPublisher || !ballPublisher || !scoreBarPublisher)
	{
		SDL_Log("Scene::setupTextureObserver - Failed to cast Objects to texture builder.");
		return;
	}

	ballPublisher->addListener(textureSubscriber);
	boardPublisher->addListener(textureSubscriber);
	computerPublisher->addListener(textureSubscriber);
	playerPublisher->addListener(textureSubscriber);
	scoreBarPublisher->addListener(textureSubscriber);
}
