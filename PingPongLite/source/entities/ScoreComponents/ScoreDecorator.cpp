#include "ScoreDecorator.h"

void ScoreDecorator::update()
{
}

void ScoreDecorator::render()
{
	std::string score_text = std::to_string(score);
	FontHandler::get().drawText(FONT::CALIBRI, score_text.c_str(), &position, 32, color);

	// Draw left side bar
	SDL_FRect leftBarGlobalPos = sideBarDestination;
	leftBarGlobalPos.x *= -1.f;
	leftBarGlobalPos.x += position.x;
	TextureHandler::get().drawTexture(TEXTURE::SCORE_BAR, leftBarGlobalPos, SDL_FLIP_NONE);

	// Draw right side bar
	SDL_FRect rightBarGlobalPos = sideBarDestination;
	rightBarGlobalPos.x += position.x;
	TextureHandler::get().drawTexture(TEXTURE::SCORE_BAR, rightBarGlobalPos, SDL_FLIP_HORIZONTAL);
}
