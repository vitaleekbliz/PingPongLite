#include "TextureComponent.h"

void TextureComponent::setMetaData(const std::string& fileName, int w, int h)
{
	this->fileName = fileName;
	width = w;
	height = h;
}

bool TextureComponent::loadMedia()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath += baseFolder;
	fullPath += fileName;

	SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
	if (!surface)
	{
		printf("Couldn't load png: %s\n", SDL_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(SDLHandler::get().getRenderer(), surface);

	if (!texture)
	{
		printf("Couldn't create texture: %s", SDL_GetError());
		return false;
	}

	return true;
}

void TextureComponent::draw(SDL_FRect destination, SDL_FlipMode flipMode, bool centerImage)
{
	// calculate texture offset
	if (centerImage)
	{
		destination.x -= destination.w / 2;
		destination.y -= destination.h / 2;
	}

	SDL_RenderTextureRotated(SDLHandler::get().getRenderer(), texture, NULL, &destination, 0, NULL, flipMode);
}
