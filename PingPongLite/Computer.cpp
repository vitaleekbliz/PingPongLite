#include "Computer.h"

Computer::Computer()
{
	offset = 50;
	speed = 1000;
	minHeight = 100;
	// TODO bug (priority HIGH) height was not initialized (height is init during texture loading)
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - (/*height*/ 120 / 2);
	position = {offset, 400};
}

void Computer::onTextureLoaded()
{
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - (height / 2);
}

void Computer::update()
{
	followBall();
	keepInBounds();
}

void Computer::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_FRect destination = SDL_FRect();
	destination.x = position.first - texture->w / 2;
	destination.y = position.second - texture->h / 2;
	destination.h = height;
	destination.w = width;

	SDL_RenderTexture(renderer, texture, NULL, &destination);
}

void Computer::setBallReference(std::weak_ptr<Object> ball)
{
	ballReference = ball;
}

void Computer::keepInBounds()
{
	if (position.second < minHeight)
	{
		position.second = minHeight;
	}
	else if (position.second > maxHeight)
	{
		position.second = maxHeight;
	}
}

void Computer::followBall()
{
	float deltaTime = SDLHandler::get().getTick();

	if (auto ball = ballReference.lock())
	{
		float ballY = ball->getPosition().second;

		float distanceToBall = ballY - position.second;

		float moveAmount = deltaTime * speed;

		if (moveAmount > std::abs(distanceToBall))
		{
			position.second = ball->getPosition().second;
		}
		else
		{
			position.second += (distanceToBall > 0 ? 1 : -1) * moveAmount;
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
