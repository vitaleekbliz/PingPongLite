#include "EffectHandler.h"

EffectHandler::~EffectHandler()
{
	close();
}

SDL_Texture* EffectHandler::getTexture(EFFECT effect)
{
	switch (effect)
	{
	case EFFECT::RED_START:
		return redStart;
	case EFFECT::RED_LOOP:
		return redLoop;
	case EFFECT::RED_END:
		return redEnd;
	case EFFECT::BLUE_START:
		return blueStart;
	case EFFECT::BLUE_LOOP:
		return blueLoop;
	case EFFECT::BLUE_END:
		return blueEnd;
	}

	return NULL;
}

EffectHandler& EffectHandler::get()
{
	static EffectHandler instance;
	return instance;
}

void EffectHandler::init()
{

	redStart = loadTexture("red_start.png");
	redLoop = loadTexture("red_loop.png");
	redEnd = loadTexture("red_end.png");
	blueStart = loadTexture("blue_start.png");
	blueLoop = loadTexture("blue_loop.png");
	blueEnd = loadTexture("blue_end.png");
}

void EffectHandler::close()
{
	SDL_DestroyTexture(redStart);
	SDL_DestroyTexture(redLoop);
	SDL_DestroyTexture(redEnd);
	SDL_DestroyTexture(blueStart);
	SDL_DestroyTexture(blueLoop);
	SDL_DestroyTexture(blueEnd);
}

void EffectHandler::drawEffect(EFFECT effect, SDL_FRect source, SDL_FRect destination, SDL_FlipMode flip,
							   bool isWorldPosition)
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	if (isWorldPosition)
	{
		destination.x -= destination.w / 2;
		destination.y -= destination.h / 2;
	}

	SDL_RenderTextureRotated(renderer, getTexture(effect), &source, &destination, 0, NULL, flip);
}

SDL_Texture* EffectHandler::loadTexture(std::string fileName)
{
	SDL_Renderer* renderer = SDLHandler::get().getRenderer();

	std::string basePath = SDL_GetBasePath();
	std::string fullPath = basePath + effectsAssetFolder + fileName;

	SDL_Surface* surface;
	surface = SDL_LoadPNG(fullPath.c_str());
	if (!surface)
	{
		SDL_Log("Couldn't load %s: %s", fullPath.c_str(), SDL_GetError());
		return NULL;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	if (!texture)
	{
		SDL_Log("Couldn't create texture from surface: %s", SDL_GetError());
		return NULL;
	}

	return texture;
}
