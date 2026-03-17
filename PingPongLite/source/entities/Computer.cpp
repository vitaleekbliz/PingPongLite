#include "Computer.h"

Computer::Computer()
{
	setupTexture();
	initVariables();
}

void Computer::update()
{
	followBall();
	keepInBounds();
}

void Computer::render()
{
	drawPaddle();
}

void Computer::setBallReference(std::weak_ptr<Object> ball)
{
	ballReference = ball;
}

void Computer::initVariables()
{
	currentSpeed = baseSpeed;
	topBoundary = SDLHandler::get().WINDOW_HEIGHT - (height / 2);
	position = {screenEdgeOffset, 400};
}

void Computer::setupTexture()
{
	textureComponent->setMetaData(textureName, width, height);
	textureComponent->loadMedia();
}

void Computer::keepInBounds()
{
	if (position.second < bottomBoundary)
	{
		position.second = bottomBoundary;
	}
	else if (position.second > topBoundary)
	{
		position.second = topBoundary;
	}
}

void Computer::followBall()
{

	float deltaTime = SDLHandler::get().getTick();

	if (auto ball = ballReference.lock())
	{
		float ballY = ball->getPosition().second;

		float deltaY = ballY - position.second;

		float moveAmount = deltaTime * currentSpeed;

		if (moveAmount > std::abs(deltaY))
		{
			position.second = ball->getPosition().second;
		}
		else
		{
			position.second += (deltaY > 0 ? 1 : -1) * moveAmount;
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

void Computer::drawPaddle()
{

	SDL_FRect destination = SDL_FRect();
	destination.x = position.first;
	destination.y = position.second;
	destination.h = height;
	destination.w = width;

	textureComponent->draw(destination, SDL_FLIP_NONE, true);
}
