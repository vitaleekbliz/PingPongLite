#pragma once
#include "core/SDLHandler.h";
#include "entities/Object.h";
#include "interfaces/ballObserver/BallPublisher.h"
#include <cmath>
#include <memory>

enum class BOUNDARY : char
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NONE
};

class Movement
{
  protected:
	void setRandomDirection();
	void applyMovement(SDL_FPoint* pos);

	void onPaddleHit(bool player);

	BOUNDARY checkBoundaries(SDL_FPoint* pos);

	const float baseSpeed = 500.f;
	float currentSpeed = baseSpeed;
	SDL_FPoint basePosition = {640, 360};

  private:
	void accelerate();

	SDL_FPoint direction = {0.f, 0.f};

	const float speedMultiplier = 1.3;
	const float maxSpeed = 1600.f;

	float leftBoundary = 15;
	float rightBoundary = 1280 - 15;
	float topBoundary = 15 + 40;
	float bottomBoundary = 720 - 15;
};
