#include "Board.h"

Board::Board()
{
	position = {640, 380};
	size = {1280, 680};
}

void Board::render()
{
	SDL_FRect destination = getCollider();
	requestDrawTexture(TEXTURE::BOARD, destination, SDL_FLIP_NONE);
}
