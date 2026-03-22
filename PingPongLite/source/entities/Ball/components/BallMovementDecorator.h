#pragma once
#include "core/SDLHandler.h";
#include "entities/Object.h";
#include <cmath>
#include <memory>
#include <numbers>

enum class BOUNDARY : char
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NONE
};

class BallMovementDecorator
{
  public:
	void setRandomDirection();
	void applyMovement(SDL_FPoint* pos);

	void onPaddleHit(SDL_FPoint* ballPos, SDL_FRect paddleRect);
	void onWallHit();

	BOUNDARY checkBoundaries(SDL_FPoint* pos);

	const float baseSpeed = 500.f;
	float currentSpeed = baseSpeed;
	SDL_FPoint basePosition = {640, 360};

  private:
	void accelerate();
	void clampVerticalVelocity();

	SDL_FPoint direction = {0.f, 0.f};
	const float verticalClampingFactor = 1.13;

	const float speedMultiplier = 1.3;
	const float maxSpeed = 1600.f;

	float leftBoundary = 15;
	float rightBoundary = 1280 - 15;
	float topBoundary = 15 + 40;
	float bottomBoundary = 720 - 15;
};
