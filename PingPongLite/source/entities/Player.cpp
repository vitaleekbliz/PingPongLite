#include "Player.h"

Player::Player()
{
	size.x = 17;
	size.y = 120;
	position = {1280 - 50, 400};
}

void Player::update()
{
	followMouse();
	keepInBounds();
}

void Player::render()
{
	SDL_FRect destination = getCollider();
	requestDraw(TEXTURE::PLAYER, destination, SDL_FLIP_NONE);
}

void Player::keepInBounds()
{
	if (position.y > bottomBoundary)
	{
		position.y = bottomBoundary;
	}
	else if (position.y < topBoundary)
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
