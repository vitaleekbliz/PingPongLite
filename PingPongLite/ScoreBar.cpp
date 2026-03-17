#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	roundDurationSeconds = 0;
}

void ScoreBar::update(float deltaTime)
{
	roundDurationSeconds += deltaTime;
}

void ScoreBar::render()
{
	// TODO refactor this function
	auto renderer = SDLHandler::get().getRenderer();

	SDL_FRect destination = SDL_FRect();
	destination.x = 0;
	destination.y = 0;

	destination.h = height;
	destination.w = width;
	SDL_RenderTextureRotated(renderer, texture, NULL, &destination, 0, NULL, SDL_FLIP_NONE);

	destination.x = 680;
	destination.y = 0;

	destination.h = height;
	destination.w = width;
	SDL_RenderTextureRotated(renderer, texture, NULL, &destination, 0, NULL, SDL_FLIP_HORIZONTAL);
}
