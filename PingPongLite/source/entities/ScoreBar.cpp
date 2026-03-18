#include "ScoreBar.h"

void ScoreBar::update()
{
	float deltaTime = SDLHandler::get().getTick();
	roundDurationSeconds += deltaTime;
}

void ScoreBar::render()
{
	requestDraw(TEXTURE::SCORE_BAR, UI.leftBar, SDL_FLIP_NONE);
	requestDraw(TEXTURE::SCORE_BAR, UI.rightBar, SDL_FLIP_HORIZONTAL);

	drawTime();

	drawScore(300, 20, computerScore);
	drawScore(SDLHandler::get().WINDOW_WIDTH - 300, 20, playerScore);
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

void ScoreBar::drawTime()
{
	auto renderer = SDLHandler::get().getRenderer();
	int x = 620;
	int y = 20;
	int minutes = roundDurationSeconds / 60;
	int seconds = (int)roundDurationSeconds % 60;

	std::string current_time = std::to_string(minutes) + (seconds > 9 ? " : " : " : 0") + std::to_string(seconds);

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDebugText(renderer, x, y, current_time.c_str());
}

void ScoreBar::drawScore(int x, int y, int score)
{
	auto renderer = SDLHandler::get().getRenderer();

	std::string text = std ::to_string(score);

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDebugText(renderer, x, y, text.c_str());
}

void ScoreBar::changeScore(bool win)
{
	if (win)
		playerScore++;
	else
		computerScore++;
}
