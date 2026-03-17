#include "TextureComponent.h"

void TextureComponent::setMetaData(const std::string& fileName, const std::string& baseFolder, int w, int h)
{
	this->fileName = fileName;
	this->baseFolder = baseFolder;
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

	onTextureLoaded();

	return true;
}
