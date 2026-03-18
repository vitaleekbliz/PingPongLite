#pragma once
#include "core/SDLHandler.h"

enum class TEXTURE : char
{
	BOARD,
	BALL,
	COMPUTER,
	PLAYER,
	SCORE_BAR
};

class TextureHandler
{
  public:
	TextureHandler() = default;
	~TextureHandler() = default;

	void init();
	void close();

	void draw(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip) const;

  protected:
  private:
	SDL_Texture* load(std::string fileName, SDL_Renderer* renderer) const;

	SDL_Texture* board = NULL;
	SDL_Texture* ball = NULL;
	SDL_Texture* computer = NULL;
	SDL_Texture* player = NULL;
	SDL_Texture* scoreBar = NULL;

	std::string audioAssetFolder = "assets\\arts\\";
};
