#pragma once
#include "components/effects/EffectComponent.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"
#include <SDL3/SDL.h>

class ScoreDecorator : public Object
{
  public:
	ScoreDecorator();
	virtual void update() override;
	virtual void render() override;

	void increment();

	int score = 0;
	SDL_Color color = SDL_Color(255, 0, 0);
	std::string tag = "None";

  private:
	void drawSideBar(bool right);
	SDL_FRect sideBarDestination = {170, 20, 245, 40};

	const float effectOffset = 15.f;
	float effectDuration = 10.f;
	EffectComponent leftEffect, rightEffect;
};
