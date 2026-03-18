#pragma once
#include "Object.h"
#include "components/BoxColliderComponent.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <random>

class Ball : public Object, public BallPublisher
{
  public:
	Ball();
	~Ball();
	void update() override;
	void render() override;

	void setPlayerBoxCollider(std::weak_ptr<BoxColliderComponent> comp);
	void setComputerBoxCollider(std::weak_ptr<BoxColliderComponent> comp);

  private:
	void notify(BallEvent event) override;

	// Constructor refactoring
	void initVariables();
	void setupComponents();

	void drawBall();

	// resetBall
	void reset();
	void setRandomDirection();

	// update Refactoring
#pragma region update() Logic
	void applyMovement();

	void bounceTopBottom();
	void bounceLeftRight();

	void resolvePaddleCollision(std::weak_ptr<BoxColliderComponent> collider, bool forComputer);
	bool checkCollision(const SDL_FRect& rect);
#pragma endregion
	void accelerateOnImpact();

	std::weak_ptr<BoxColliderComponent> playerBoxCollider;
	std::weak_ptr<BoxColliderComponent> computerBoxCollider;

	SDL_FPoint direction;

	float currentSpeed;
	const float baseSpeed = 500.f;
	float speedMultiplier = 1.2;
	const float maxSpeed = 1600.f;

	// TODO remove crutch
	//  ball accelerating multiple times on colision -> add cooldown
	float colisionElapsed = 0.f;

	float leftBoundary;
	float rightBoundary;
	float topBoundary;
	float bottomBoundary;

	const std::string textureName = "Ball.png";
	const int width = 30;
	const int height = 30;
};
