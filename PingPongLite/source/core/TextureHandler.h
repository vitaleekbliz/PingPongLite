#pragma once
#include "core/SDLHandler.h"
#include "interfaces/textureObserver/TextureSubscriber.h"

class TextureHandler : public TextureSubscriber
{
  public:
	TextureHandler() = default;
	~TextureHandler() = default;

	void init();
	void close();

	virtual void onDrawRequest(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
							   bool isRectCentered = true) const;

  private:
	SDL_Texture* load(std::string fileName, SDL_Renderer* renderer) const;

	SDL_Texture* board = NULL;
	SDL_Texture* ball = NULL;
	SDL_Texture* computer = NULL;
	SDL_Texture* player = NULL;
	SDL_Texture* scoreBar = NULL;

	std::string audioAssetFolder = "assets\\arts\\";
};
