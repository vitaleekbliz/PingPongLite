#pragma once
#include "Object.h"
#include <random>

class Ball : public Object
{
  public:
	Ball();
	~Ball();
	void update(float deltaTime) override;
	void render() override;

  private:
	void onTextureLoaded() override;

	void resetPos();
	void setRandomDirection();

	void applyMovement(float deltaTime);

	void checkBoundaries();
	void bounceTopBottom();

	std::pair<float, float> direction;
	float speed = 500.f;
	// TODO increase ball speed using observer pattern when new minute comes ->
	float acceleration = 0.1;

	float minHeight;
	float maxHeight;
	float minWidth;
	float maxWidth;
};
