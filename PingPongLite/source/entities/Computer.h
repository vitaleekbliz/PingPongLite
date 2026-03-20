#pragma once
#include "Object.h"
#include "core/SDLHandler.h"
#include <memory>

class Computer : public Object
{
  public:
	Computer();
	void update() override;
	void render() override;
	void setBallReference(std::weak_ptr<Object> ball);

  private:
	void keepInBounds();
	void followBall();

	const int baseSpeed = 300;
	int currentSpeed = baseSpeed;

	int topBoundary = 720 - size.y / 2;
	const int bottomBoundary = 100;

	std::weak_ptr<Object> ballReference;
};
