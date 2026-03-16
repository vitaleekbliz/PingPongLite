#pragma once
#include "Object.h"

class Ball : public Object
{
  public:
	void update(float deltaTime) override;
	void render() override;

  private:
	std::pair<float, float> direction;
};
