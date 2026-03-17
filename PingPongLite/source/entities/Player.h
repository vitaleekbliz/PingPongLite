#pragma once
#include "Object.h"
#include "components/BoxColliderComponent.h"
#include "core/SDLHandler.h"

class Player : public Object
{
  public:
	Player();
	void update() override;
	void render() override;

	std::weak_ptr<BoxColliderComponent> getBoxCollider();

  private:
	void initVariables();
	void setupComponents();

	void keepInBounds();
	void followMouse();

	void drawPaddle();

	std::shared_ptr<BoxColliderComponent> boxCollider;

	int currentSpeed;
	int topBoundary;
	const int bottomBoundary = 100;

	const int baseSpeed = 1000;
	const int screenEdgeOffset = 50;

	const std::string textureName = "Player.png";
	const int width = 17;
	const int height = 120;
};
