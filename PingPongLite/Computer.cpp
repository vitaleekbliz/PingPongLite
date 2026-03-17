#include "Computer.h"

Computer::Computer()
{
	offset = 50;
	speed = 500;
	minHeight = 100;
	// TODO bug height was not initialized (height is init during texture loading)
	// Crutch hardcoded value
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - (/*height*/ 120 / 2);
	position = {offset, 400};
}

void Computer::update(float deltaTime)
{
	followBall(deltaTime);
	moveBackToBounds();
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

void Computer::moveBackToBounds()
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

void Computer::followBall(float deltaTime)
{
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
}
