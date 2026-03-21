#include "Board.h"

Board::Board()
{
	setPosition({640, 380});
	setSize({1280, 680});
}

void Board::update()
{
}

void Board::render()
{
	SDL_FRect destination = getCollider();
	TextureHandler::get().drawTexture(TEXTURE::BOARD, destination, SDL_FLIP_NONE);
}
