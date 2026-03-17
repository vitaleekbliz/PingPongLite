#include "Player.h"

Player::Player()
{
	setupComponents();
	initVariables();
}

void Player::update()
{
	boxCollider->move(position.x, position.y);

	followMouse();
	keepInBounds();
}

void Player::render()
{
	drawPaddle();
}

std::weak_ptr<BoxColliderComponent> Player::getBoxCollider()
{
	return boxCollider;
}

void Player::initVariables()
{
	currentSpeed = baseSpeed;
	topBoundary = SDLHandler::get().WINDOW_HEIGHT - (height / 2);
	position = {(float)SDLHandler::get().WINDOW_WIDTH - screenEdgeOffset, 400};
}

void Player::setupComponents()
{
	textureComponent = std::make_unique<TextureComponent>(textureName, width, height);
	boxCollider = std::make_shared<BoxColliderComponent>(width, height);
}

void Player::keepInBounds()
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

void Player::followMouse()
{
	float deltaTime = SDLHandler::get().getTick();
	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	float distanceToMouse = mouseY - position.y;
	float moveAmount = deltaTime * currentSpeed;
	if (moveAmount > std::abs(distanceToMouse))
	{
		position.y = mouseY;
	}
	else
	{
		position.y += (distanceToMouse > 0 ? 1 : -1) * moveAmount;
	}
}

void Player::drawPaddle()
{
	SDL_FRect destination = SDL_FRect();
	destination.x = position.x;
	destination.y = position.y;
	destination.h = height;
	destination.w = width;

	textureComponent->draw(destination, SDL_FLIP_NONE);
}
