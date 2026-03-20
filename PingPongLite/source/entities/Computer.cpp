#include "Computer.h"

Computer::Computer()
{
	size.x = 17;
	size.y = 120;

	position = {50, 400};
	bottomBoundary = 720 - size.y / 2;
}

void Computer::update()
{
	followBall();
	keepInBounds();
}

void Computer::render()
{
	SDL_FRect destination = getCollider();
	requestDrawTexture(TEXTURE::COMPUTER, destination, SDL_FLIP_NONE);
}

void Computer::setBallReference(std::weak_ptr<Object> ball)
{
	ballReference = ball;
}

void Computer::keepInBounds()
{
	if (position.y < topBoundary)
	{
		position.y = topBoundary;
	}
	else if (position.y > bottomBoundary)
	{
		position.y = bottomBoundary;
	}
}

void Computer::followBall()
{

	float deltaTime = SDLHandler::get().getTick();

	if (auto ball = ballReference.lock())
	{
		float ballY = ball->getPosition().y;

		float deltaY = ballY - position.y;

		float moveAmount = deltaTime * currentSpeed;

		if (moveAmount > std::abs(deltaY))
		{
			position.y = ball->getPosition().y;
		}
		else
		{
			position.y += (deltaY > 0 ? 1 : -1) * moveAmount;
		}
	}
	else
	{
		static bool warnedOnce = false;
		if (!warnedOnce)
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Computer AI: ballReference is null. AI is idling.");
			warnedOnce = true;
		}
	}
}
