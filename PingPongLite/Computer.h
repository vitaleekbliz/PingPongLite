#pragma once
#include "Object.h"
#include "SDLHandler.h"
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

	void onTextureLoaded() override;

	int offset;
	int speed;
	int maxHeight;
	int minHeight;

	std::weak_ptr<Object> ballReference;
};
