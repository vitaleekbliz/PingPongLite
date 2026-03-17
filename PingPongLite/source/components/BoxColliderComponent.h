#pragma once
#include "core/SDLHandler.h"
#include <SDL3/SDL.h>

class BoxColliderComponent
{
  public:
	BoxColliderComponent(int w, int h);
	~BoxColliderComponent();

	SDL_FRect getRect() const;
	void move(int x, int y);

  protected:
  private:
	int x, y;
	int width, height;
};
