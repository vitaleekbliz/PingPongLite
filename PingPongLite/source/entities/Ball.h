#pragma once
#include "Object.h"
#include "components/ColliderComponent.h"
#include "interfaces/ballObserver/BallPublisher.h"
#include <random>

class Ball : public Object, public BallPublisher, public ColliderComponent
{
  public:
	Ball();
	~Ball();
	void update() override;
	void render() override;

  private:
	void notify(BallEvent event) override;

	void initVariables();
	void setupComponents();

	void drawBall();

	void resetPos();
	void setRandomDirection();

	void applyMovement();

	void checkBoundaries();
	void bounceTopBottom();
	void bounceLeftRight();

	std::pair<float, float> direction;
	float speed = 500.f;
	// TODO increase ball speed using observer pattern when new minute comes ->
	float acceleration = 0.1;

	float leftBoundary;
	float rightBoundary;
	float topBoundary;
	float bottomBoundary;

	const std::string textureName = "Ball.png";
	const int width = 30;
	const int height = 30;
};
