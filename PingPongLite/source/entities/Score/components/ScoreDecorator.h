#pragma once
#include "components/effects/EffectComponent.h"
#include "core/subsystems/AudioHandler.h"
#include "core/subsystems/FontHandler.h"
#include "core/subsystems/TextureHandler.h"
#include "entities/Object.h"
#include <SDL3/SDL.h>
#include <cmath>

class ScoreDecorator : public Object
{
  public:
	ScoreDecorator();
	virtual void update() override;
	virtual void render() override;

	void add(int value);

	void upgradeColor();

	int score = 0;
	SDL_Color color = SDL_Color(255, 0, 0);
	bool isPlayerScore = false;

  private:
	void upgradeEffectPosition();

	void drawSideBar(bool right);

	SDL_FRect sideBarDestination = {190, 20, 205, 40};

	const float effectOffsetX = 40.f;
	const float effectOffsetY = -4.f;
	float effectDuration = 10.f;
	std::shared_ptr<EffectComponent> leftEffect, rightEffect;
};
