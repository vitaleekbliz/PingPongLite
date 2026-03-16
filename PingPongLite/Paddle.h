#pragma once
#include "Object.h"

class Paddle : public Object
{
  public:
	void update(float deltaTime) override;
	void render() override;
};
