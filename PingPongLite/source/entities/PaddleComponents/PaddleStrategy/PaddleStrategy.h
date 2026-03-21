#pragma once
#include "core/SDLHandler.h"

enum class PADDLE_STRATEGY : char
{
	PLAYER,
	COMPUTER
};

class PaddleStrategy
{
  public:
	virtual void track(SDL_FPoint* ownerPos) = 0;
	void setTarget(const SDL_FPoint* ballPos);

  protected:
	void keepInBounds(SDL_FPoint* ownerPos);
	const SDL_FPoint* ballPos;

	int baseSpeed = 500;
	int currentSpeed = baseSpeed;

	const int topBoundary = 100;
	const int bottomBoundary = 660;
};
