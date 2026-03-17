#pragma once
#include "Object.h"
#include "SDLHandler.h"
#include <memory>

class Computer : public Object
{
  public:
	Computer();

	void update(float deltaTime) override;
	void render() override;
	void setBallReference(std::weak_ptr<Object> ball);

  private:
	int offset;
	int speed;
	int maxHeight;
	int minHeight;

	void moveBackToBounds();
	void followBall(float deltaTime);

	std::weak_ptr<Object> ballReference;
};
