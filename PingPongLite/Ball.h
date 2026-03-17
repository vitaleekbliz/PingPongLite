#pragma once
#include "Object.h"

class Ball : public Object
{
  public:
	Ball();
	~Ball();
	void update(float deltaTime) override;
	void render() override;

  private:
	std::pair<float, float> direction;
	float speed = 1.f;
	// TODO increase ball speed using observer pattern when new minute comes ->
	float acceleration = 0.1;
};
