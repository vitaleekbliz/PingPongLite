#include "FontHandler.h"

void FontHandler::onDrawRequestText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color)
{
	drawText(position, size, id, text, color);
}

void FontHandler::drawText(SDL_FPoint* position, int size, FONT id, std::string text, SDL_Color color)
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	// load texture block
	std::string basePath = SDL_GetBasePath();
	std::string assetPath = basePath + fontAssetFolder;
	std::string fullPath = assetPath + getFontName(id);
	TTF_Font* font = TTF_OpenFont(fullPath.c_str(), size);

	if (!font)
	{
		SDL_Log("Couldn't load font %s : %s\n", fullPath.c_str(), SDL_GetError());
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), color);
	TTF_CloseFont(font);

	if (!surface)
	{
		SDL_Log("Couldn't load surace from font %s : %s\n", fullPath.c_str(), SDL_GetError());
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	if (!texture)
	{
		SDL_Log("Couldn't load texture from surface %s : %s\n", fullPath.c_str(), SDL_GetError());
		return;
	}

	// get texture size
	SDL_FRect destination = SDL_FRect();
	SDL_GetTextureSize(texture, &destination.w, &destination.h);

	// center texture
	destination.x = position->x - destination.w / 2;
	destination.y = position->y - destination.h / 2;

	SDL_RenderTexture(renderer, texture, NULL, &destination);

	SDL_DestroyTexture(texture);
}

std::string FontHandler::getFontName(FONT id)
{
	switch (id)
	{
	case FONT::CALIBRI:
		return "calibri.ttf";
		break;
	}

	return "";
}
