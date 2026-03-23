#pragma once
#include "core/SDLHandler.h"
#include <string>

enum class EFFECT : char
{
	RED_START,
	RED_LOOP,
	RED_END,
	BLUE_START,
	BLUE_LOOP,
	BLUE_END,
};

class EffectHandler
{
  public:
	EffectHandler(const EffectHandler&) = delete;
	EffectHandler& operator=(const EffectHandler&) = delete;
	static EffectHandler& get();

	void init();
	void close();

	void drawEffect(EFFECT effect, SDL_FRect source, SDL_FRect destination, SDL_FlipMode flip,
					bool isWorldPosition = true);

  private:
	EffectHandler() = default;
	~EffectHandler();

	SDL_Texture* loadTexture(std::string fileName);
	SDL_Texture* getLoadedTexture(EFFECT effect);

	// TEMP DEBUG REMOVE
	//---
  public:
	//---
	SDL_Texture* redStart = NULL;
	SDL_Texture* redLoop = NULL;
	SDL_Texture* redEnd = NULL;
	SDL_Texture* blueStart = NULL;
	SDL_Texture* blueLoop = NULL;
	SDL_Texture* blueEnd = NULL;

	std::string effectsAssetFolder = "assets\\effects\\";
};
