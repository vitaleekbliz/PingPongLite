#pragma once
#include "BallPublisher.h"
#include "Object.h"
#include <random>

class Ball : public Object, public BallPublisher
{
  public:
	Ball();
	~Ball();
	void update() override;
	void render() override;

  private:
	void notify(BallEvent event) override;
	void onTextureLoaded() override;

	void reset();
	void setRandomDirection();

	void applyMovement();

	void checkBoundaries();
	void bounceTopBottom();
	void bounceLeftRight();

	std::pair<float, float> direction;
	float speed = 500.f;
	// TODO increase ball speed using observer pattern when new minute comes ->
	float acceleration = 0.1;

	float minHeight;
	float maxHeight;
	float minWidth;
	float maxWidth;
};
