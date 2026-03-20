#pragma once
#include "Object.h"
#include "core/SDLHandler.h"

class Player : public Object
{
  public:
	Player();
	void update() override;
	void render() override;

  private:
	void keepInBounds();
	void followMouse();

	const int topBoundary = 100;
	int bottomBoundary = 1200;

	int baseSpeed = 1000;
	int currentSpeed = baseSpeed;
};
