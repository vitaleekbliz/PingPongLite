#include "Paddle.h"

Paddle::Paddle()
{
	setSize({17, 120});
}

void Paddle::update()
{
	strategy->track(&position);
}

void Paddle::render()
{
	SDL_FRect destination = getCollider();
	SDL_FlipMode flipMode = (currentStrategy == originalStrategy ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

	switch (currentStrategy)
	{
	case PADDLE_STRATEGY::PLAYER:
		TextureHandler::get().drawTexture(TEXTURE::PLAYER, destination, flipMode);
		break;
	case PADDLE_STRATEGY::COMPUTER:
		TextureHandler::get().drawTexture(TEXTURE::COMPUTER, destination, flipMode);
		break;
	}
}

void Paddle::setOriginalStrategy(PADDLE_STRATEGY id, std::shared_ptr<Object> ball)
{
	this->trackingObject = ball;

	originalStrategy = id;
	changeStrategy(id);
}

void Paddle::onStrategyChange()
{
	changeStrategy(currentStrategy == PADDLE_STRATEGY::PLAYER ? PADDLE_STRATEGY::COMPUTER : PADDLE_STRATEGY::PLAYER);
}

void Paddle::changeStrategy(PADDLE_STRATEGY id)
{
	currentStrategy = id;

	switch (id)
	{
	case PADDLE_STRATEGY::PLAYER:
		strategy = std::make_shared<PaddlePlayerStrategy>();
		break;
	case PADDLE_STRATEGY::COMPUTER:
		strategy = std::make_shared<PaddleComputerStrategy>();
		break;
	}

	strategy->setTarget(trackingObject.lock());
}
