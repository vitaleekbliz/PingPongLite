#include "Board.h"

void Board::update(float deltaTime)
{
}

void Board::render()
{
	SDL_FRect destination = SDL_FRect();
	// Score Bar offset
	destination.y = 40;
	destination.h = height;
	destination.w = width;
	SDL_RenderTexture(SDLHandler::get().getRenderer(), texture, NULL, &destination);
}
