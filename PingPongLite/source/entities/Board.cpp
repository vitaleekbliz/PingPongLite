#include "Board.h"

Board::Board()
{
	textureComponent = std::make_unique<TextureComponent>(textureName, width, height);
}

Board::~Board()
{
}

void Board::update()
{
}

void Board::render()
{
	drawBoard();
}

void Board::drawBoard()
{
	SDL_FRect destination = SDL_FRect();
	destination.y = topDrawOffset;
	destination.h = height;
	destination.w = width;
	textureComponent->draw(destination, SDL_FLIP_NONE, false);
}
