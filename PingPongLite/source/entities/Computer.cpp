#include "Computer.h"

Computer::Computer()
{
	size.x = width;
	size.y = height;
	setupComponents();
	initVariables();
}

void Computer::update()
{
	boxCollider->move(position.x, position.y);
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

std::weak_ptr<BoxColliderComponent> Computer::getBoxCollider()
{
	return boxCollider;
}

void Computer::initVariables()
{
	currentSpeed = baseSpeed;
	topBoundary = SDLHandler::get().WINDOW_HEIGHT - (height / 2);
	position = {(float)screenEdgeOffset, 400};
}

void Computer::setupComponents()
{
	textureComponent = std::make_unique<TextureComponent>(textureName, width, height);
	boxCollider = std::make_shared<BoxColliderComponent>(width, height);
}

void Computer::keepInBounds()
{
	if (position.y < bottomBoundary)
	{
		position.y = bottomBoundary;
	}
	else if (position.y > topBoundary)
	{
		position.y = topBoundary;
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

void Computer::drawPaddle()
{

	SDL_FRect destination = SDL_FRect();
	destination.x = position.x;
	destination.y = position.y;
	destination.h = height;
	destination.w = width;

	textureComponent->draw(destination, SDL_FLIP_NONE, true);
}
