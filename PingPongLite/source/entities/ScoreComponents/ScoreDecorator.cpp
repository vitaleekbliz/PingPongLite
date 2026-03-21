#include "ScoreDecorator.h"

void ScoreDecorator::update()
{
}

void ScoreDecorator::render()
{
	std::string score_text = std::to_string(score);
	requestDrawText(FONT::CALIBRI, score_text.c_str(), &position, 32, color);

	// Draw left side bar
	SDL_FRect leftBarGlobalPos = sideBarLocalDestination;
	leftBarGlobalPos.x *= -1;
	leftBarGlobalPos.x += position.x;
	requestDrawTexture(TEXTURE::SCORE_BAR, leftBarGlobalPos, SDL_FLIP_NONE, true);

	// Draw right side bar
	SDL_FRect rightBarGlobalPos = sideBarLocalDestination;
	rightBarGlobalPos.x += position.x;
	requestDrawTexture(TEXTURE::SCORE_BAR, rightBarGlobalPos, SDL_FLIP_HORIZONTAL, true);
}
