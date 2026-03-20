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
		requestDrawTexture(TEXTURE::PLAYER, destination, flipMode);
		break;
	case PADDLE_STRATEGY::COMPUTER:
		requestDrawTexture(TEXTURE::COMPUTER, destination, flipMode);
		break;
	}
}

void Paddle::setOriginalStrategy(PADDLE_STRATEGY id, const SDL_FPoint* ballPos)
{
	this->ballPos = ballPos;

	originalStrategy = id;
	changeStrategy(id);
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

	strategy->setTarget(ballPos);
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
		std::string messeage = "Switching places in ";
		messeage += std::to_string(timer);
		SDL_FPoint pos = {640, 360};
		SDL_Color color = SDL_Color();
		color.r = 255;
		requestDrawText(FONT::CALIBRI, messeage, &pos, 36, color);
	}
}
