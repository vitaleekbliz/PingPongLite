#pragma once
#include <SDL3/SDL.h>

class ColliderComponent
{
  public:
	// float width, height;

	SDL_FRect getRect(float x, float y) const;

  protected:
  private:
};
