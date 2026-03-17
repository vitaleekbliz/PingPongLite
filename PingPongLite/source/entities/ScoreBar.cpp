#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
	setupTexture();
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

void ScoreBar::setupTexture()
{
	textureComponent->setMetaData(textureName, width, height);
	textureComponent->loadMedia();
}

void ScoreBar::drawTopBar()
{

	SDL_FRect destination = SDL_FRect();
	destination.x = 0;
	destination.y = 0;
	destination.h = height;
	destination.w = width;
	textureComponent->draw(destination, SDL_FLIP_NONE, false);

	destination.x = 680;
	destination.y = 0;
	destination.h = height;
	destination.w = width;
	textureComponent->draw(destination, SDL_FLIP_HORIZONTAL, false);
}

void ScoreBar::changeScore(bool win)
{
	if (win)
		playerScore++;
	else
		computerScore++;
}
