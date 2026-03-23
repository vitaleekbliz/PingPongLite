#pragma once
#include "core/SDLHandler.h"
#include <string>

enum class TEXTURE : char
{
	BALL,
	BOARD,
	COMPUTER,
	PLAYER,
	SCORE_BAR
};

class TextureHandler
{
  public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	static TextureHandler& get();

	void init();
	void close();

	void drawTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip, bool isWorldPosition = true);

  private:
	TextureHandler() = default;
	~TextureHandler();

	SDL_Texture* loadTexture(std::string fileName);
	SDL_Texture* getLoadedTexture(TEXTURE texture);

	SDL_Texture* board = NULL;
	SDL_Texture* ball = NULL;
	SDL_Texture* computer = NULL;
	SDL_Texture* player = NULL;
	SDL_Texture* scoreBar = NULL;

	std::string audioAssetFolder = "assets\\arts\\";
};
