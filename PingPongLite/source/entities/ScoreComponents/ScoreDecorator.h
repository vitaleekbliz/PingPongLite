#pragma once
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"
#include <SDL3/SDL.h>

class ScoreDecorator : public Object
{
  public:
	virtual void update() override;
	virtual void render() override;

	int score = 0;
	SDL_Color color = SDL_Color(255, 0, 0);

  private:
	SDL_FRect sideBarDestination = {170, 20, 245, 40};
};
