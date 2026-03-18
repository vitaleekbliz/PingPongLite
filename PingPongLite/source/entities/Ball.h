#pragma once
#include "Object.h"
#include "core/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher
{
  public:
	Ball();
	void update() override;
	void render() override;

	void setPlayerReference(std::weak_ptr<Object> player);
	void setComputerReference(std::weak_ptr<Object> computer);

  private:
	virtual void notify(BallEvent event) override;

	// resetBall
	void reset();
	void setRandomDirection();

	// update Refactoring
#pragma region update() Logic
	void applyMovement();

	void bounceTopBottom();
	void bounceLeftRight();

	void resolvePaddleCollision();
	bool checkCollision(const SDL_FRect rect);
#pragma endregion

	void accelerateOnImpact();

	bool isCollidingPaddle = false;

	std::weak_ptr<Object> playerObject;
	std::weak_ptr<Object> computerObject;

	SDL_FPoint direction = {0.f, 0.f};
	SDL_FPoint basePosition = {640, 360};

	const float baseSpeed = 500.f;
	float currentSpeed = baseSpeed;
	const float speedMultiplier = 1.2;
	const float maxSpeed = 1600.f;

	float leftBoundary = 15;
	float rightBoundary = 1280 - 15;
	float topBoundary = 15 + 40;
	float bottomBoundary = 720 - 15;
};
