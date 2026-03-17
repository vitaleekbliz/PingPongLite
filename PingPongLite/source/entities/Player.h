#pragma once
#include "Object.h"
#include "components/ColliderComponent.h"
#include "core/SDLHandler.h"

class Player : public Object, public ColliderComponent
{
  public:
	Player();
	void update() override;
	void render() override;

  private:
	void initVariables();
	void setupTexture();

	void keepInBounds();
	void followMouse();

	void drawPaddle();

	int currentSpeed;
	int topBoundary;
	const int bottomBoundary = 100;

	const int baseSpeed = 1000;
	const int screenEdgeOffset = 50;

	const std::string textureName = "Player.png";
	const int width = 17;
	const int height = 120;
};
