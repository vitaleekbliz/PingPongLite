#pragma once
#include <SDL3/SDL.h>

class PaddleHitSubscriber
{
  public:
	virtual ~PaddleHitSubscriber() = default;
	virtual void onPaddleHit(const SDL_FRect& paddleCollider) = 0;
};