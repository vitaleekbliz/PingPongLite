#include "Paddle.h"

Paddle::Paddle()
{
	setSize({17, 120});
}

void Paddle::update()
{
	strategy->track(&position);

	DEBUG_handleControllerSwitch();
}

void Paddle::render()
{
	DEBUG_printWarning();

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

void Paddle::changeStrategy(PADDLE_STRATEGY id)
{
	notifyStrategyChange();

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

void Paddle::notifyStrategyChange()
{
	for (auto it = strategySubscribers.begin(); it != strategySubscribers.end();)
	{
		if (auto subscriber = it->lock())
		{
			subscriber->onStrategyChange();
			it++;
		}
		else
		{
			it = strategySubscribers.erase(it);
		}
	}
}

void Paddle::DEBUG_handleControllerSwitch()
{
	timer -= SDLHandler::get().getTick();
	if (timer < 0.f)
	{
		timer = cooldown;
		if (currentStrategy == PADDLE_STRATEGY::PLAYER)
		{
			changeStrategy(PADDLE_STRATEGY::COMPUTER);
		}
		else
		{
			changeStrategy(PADDLE_STRATEGY::PLAYER);
		}
	}
}

void Paddle::DEBUG_printWarning()
{
	if (timer < 5.f)
	{
		std::string messeage = "Changing Paddle strategy in ";
		messeage += std::to_string(timer);
		SDL_FPoint pos = {640, 360};
		SDL_Color color = SDL_Color();
		color.r = 255;
		FontHandler::get().drawText(FONT::CALIBRI, messeage, &pos, 36, color);
	}
}
