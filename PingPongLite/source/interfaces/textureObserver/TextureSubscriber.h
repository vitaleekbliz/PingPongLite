#pragma once
#include <SDL3/SDL.h>

enum class TEXTURE : char
{
	BOARD,
	BALL,
	COMPUTER,
	PLAYER,
	SCORE_BAR
};

class TextureSubscriber
{
  public:
	virtual ~TextureSubscriber() = default;
	virtual void onDrawRequestTexture(TEXTURE texture, SDL_FRect destination, SDL_FlipMode flip,
									  bool isRectCentered) = 0;
};