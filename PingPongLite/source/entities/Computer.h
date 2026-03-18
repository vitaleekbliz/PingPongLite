#pragma once
#include "Object.h"
#include "components/BoxColliderComponent.h"
#include "core/SDLHandler.h"
#include <memory>

class Computer : public Object
{
  public:
	Computer();

	void update() override;
	void render() override;
	void setBallReference(std::weak_ptr<Object> ball);

	std::weak_ptr<BoxColliderComponent> getBoxCollider();

  private:
	void initVariables();
	void setupComponents();

	void keepInBounds();
	void followBall();

	void drawPaddle();

	int currentSpeed;

	const int screenEdgeOffset = 50;
	const int baseSpeed = 200;

	int topBoundary;
	const int bottomBoundary = 100;

	std::weak_ptr<Object> ballReference;
	std::shared_ptr<BoxColliderComponent> boxCollider;

	const std::string textureName = "Computer.png";
	const int width = 17;
	const int height = 120;
};
