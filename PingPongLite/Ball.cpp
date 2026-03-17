#include "Ball.h"

Ball::Ball()
{
	position = {SDLHandler::get().WINDOW_WIDTH / 2, SDLHandler::get().WINDOW_HEIGHT / 2};
	direction = {-1, 0};
}

Ball::~Ball()
{
}

void Ball::update(float deltaTime)
{
}

void Ball::render()
{
	auto renderer = SDLHandler::get().getRenderer();

	SDL_FRect destination = SDL_FRect();
	destination.x = position.first - width / 2;
	destination.y = position.second - height / 2;

	destination.h = height;
	destination.w = width;
	SDL_RenderTexture(renderer, texture, NULL, &destination);
}