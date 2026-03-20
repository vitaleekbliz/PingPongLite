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

	const int baseSpeed = 500;
	int currentSpeed = baseSpeed;

	const int topBoundary = 100;
	int bottomBoundary = 1200;

	std::weak_ptr<Object> ballReference;
};
