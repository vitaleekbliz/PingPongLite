#include "ScoreBar.h"

void ScoreBar::update()
{
	float deltaTime = SDLHandler::get().getTick();
	roundDurationSeconds += deltaTime;
}

void ScoreBar::render()
{
	// Draw bars
	// requestDrawTexture(TEXTURE::SCORE_BAR, ui.leftBar, SDL_FLIP_NONE);
	// requestDrawTexture(TEXTURE::SCORE_BAR, ui.rightBar, SDL_FLIP_HORIZONTAL);

	// Draw time START
	int minutes = roundDurationSeconds / 60;
	int seconds = (int)roundDurationSeconds % 60;
	std::string current_time = std::to_string(minutes) + (seconds > 9 ? " : " : " : 0") + std::to_string(seconds);

	SDL_Color color = SDL_Color(211, 211, 211);
	requestDrawText(FONT::CALIBRI, current_time.c_str(), &ui.time, 32, color);
	// END

	// Draw Score
	color = SDL_Color(82, 124, 215);
	std::string score_text = std::to_string(computerScore);
	requestDrawText(FONT::CALIBRI, score_text.c_str(), &ui.scoreLeft, 32, color);

	color = SDL_Color(215, 121, 82);
	score_text = std::to_string(playerScore);
	requestDrawText(FONT::CALIBRI, score_text.c_str(), &ui.scoreRight, 32, color);
}

void ScoreBar::onBallEvent(BallEvent event)
{
	switch (event)
	{
	case BallEvent::GOAL_LEFT:
		playerScore++;
		break;
	case BallEvent::GOAL_RIGHT:
		computerScore++;
		break;
	}
}
