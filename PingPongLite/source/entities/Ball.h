#pragma once
#include "Object.h"
#include "core/Texturehandler.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher
{
  public:
	Ball();
	~Ball() = default;
	void update() override;
	void render() override;

	void setPlayerReference(std::weak_ptr<Object> player);
	void setComputerReference(std::weak_ptr<Object> computer);

  private:
	void notify(BallEvent event) override;

	// resetBall
	void reset();
	void setRandomDirection();

	// update Refactoring
#pragma region update() Logic
	void applyMovement();

	void bounceTopBottom();
	void bounceLeftRight();

	void resolvePaddleCollision(std::weak_ptr<Object> object, bool forComputer);
	bool checkCollision(const SDL_FRect rect);
#pragma endregion

	void accelerateOnImpact();

	std::weak_ptr<Object> playerObject;
	std::weak_ptr<Object> computerObject;

	SDL_FPoint direction = {0.f, 0.f};

	const std::string textureName = "Ball.png";
	const int width = 30;
	const int height = 30;

	const float baseSpeed = 500.f;
	float currentSpeed = baseSpeed;
	float speedMultiplier = 1.2;
	const float maxSpeed = 1600.f;

	// TODO remove crutch
	//  ball accelerating multiple times on colision -> add cooldown
	float colisionElapsed = 0.f;

	float leftBoundary = width / 2;
	float rightBoundary = SDLHandler::get().WINDOW_WIDTH - width / 2;
	float topBoundary = height / 2 + 40;
	float bottomBoundary = SDLHandler::get().WINDOW_HEIGHT - height / 2;
};
