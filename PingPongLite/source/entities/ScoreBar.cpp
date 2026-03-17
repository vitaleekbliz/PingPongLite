#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	roundDurationSeconds = 0;
	computerScore = 0;
	playerScore = 0;
}

void ScoreBar::update()
{
	float deltaTime = SDLHandler::get().getTick();
	roundDurationSeconds += deltaTime;
}

void ScoreBar::render()
{
	drawTopBar();
}

void ScoreBar::onBallEvent(BallEvent event)
{
	switch (event)
	{
	case BallEvent::GOAL_LEFT:
		changeScore(true);
		break;
	case BallEvent::GOAL_RIGHT:
		changeScore(false);
		break;
	default:
		break;
	}
}

void ScoreBar::drawTopBar()
{
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

void ScoreBar::changeScore(bool win)
{
	if (win)
		playerScore++;
	else
		computerScore++;
}
