#include "Player.h"

Player::Player()
{
	offset = 50;
	speed = 500;
	minHeight = 100;
	// TODO bug height was not initialized (height is init during texture loading)
	// Crutch hardcoded value
	maxHeight = SDLHandler::get().WINDOW_HEIGHT - (/*height*/ 120 / 2);
	position = {SDLHandler::get().WINDOW_WIDTH - offset, 400};
}

void Player::update(float deltaTime)
{
	followMouse(deltaTime);
	moveBackToBounds();
}

void Player::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_FRect destination = SDL_FRect();
	destination.x = position.first - texture->w / 2;
	destination.y = position.second - texture->h / 2;
	destination.h = height;
	destination.w = width;

	SDL_RenderTexture(renderer, texture, NULL, &destination);
}

void Player::moveBackToBounds()
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

void Player::followMouse(float deltaTime)
{
	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	float distanceToMouse = mouseY - position.second;
	float moveAmount = deltaTime * speed;
	if (moveAmount > std::abs(distanceToMouse))
	{
		position.second = mouseY;
	}
	else
	{
		position.second += (distanceToMouse > 0 ? 1 : -1) * moveAmount;
	}
}
