#include "Player.h"

Player::Player()
{
	setupTexture();
	initVariables();
}

void Player::update()
{
	followMouse();
	keepInBounds();
}

void Player::render()
{
	drawPaddle();
}

void Player::initVariables()
{
	currentSpeed = baseSpeed;
	topBoundary = SDLHandler::get().WINDOW_HEIGHT - (height / 2);
	position = {SDLHandler::get().WINDOW_WIDTH - screenEdgeOffset, 400};
}

void Player::setupTexture()
{
	textureComponent->setMetaData(textureName, width, height);
	textureComponent->loadMedia();
}

void Player::keepInBounds()
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

void Player::followMouse()
{
	float deltaTime = SDLHandler::get().getTick();
	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	float distanceToMouse = mouseY - position.second;
	float moveAmount = deltaTime * currentSpeed;
	if (moveAmount > std::abs(distanceToMouse))
	{
		position.second = mouseY;
	}
	else
	{
		position.second += (distanceToMouse > 0 ? 1 : -1) * moveAmount;
	}
}

void Player::drawPaddle()
{
	SDL_FRect destination = SDL_FRect();
	destination.x = position.first;
	destination.y = position.second;
	destination.h = height;
	destination.w = width;

	textureComponent->draw(destination, SDL_FLIP_NONE);
}
